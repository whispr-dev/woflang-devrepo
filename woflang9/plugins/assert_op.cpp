// plugins/assert_ops.cpp
#ifndef WOFLANG_PLUGIN_EXPORT
#  ifdef _WIN32
#    define WOFLANG_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#  else
#    define WOFLANG_PLUGIN_EXPORT extern "C"
#  endif
#endif

#include "core/woflang.hpp"
#include <cmath>
#include <stdexcept>
#include <string>
#include <variant>

namespace woflang {

static inline double as_num(const WofValue& v, const char* opname){
    if (!v.is_numeric()) throw std::runtime_error(std::string(opname)+": expected numeric");
    return v.as_numeric();
}
static inline std::string as_str(const WofValue& v, const char* opname){
    if (v.type != WofType::String && v.type != WofType::Symbol)
        throw std::runtime_error(std::string(opname)+": expected string/symbol");
    return std::get<std::string>(v.value);
}

// Stack contracts (top is rightmost):
//   actual expected           expect_eq         -> (throws if not equal)
//   actual expected tol       expect_approx     -> (|a-e|<=tol)
//   cond                      expect_true       -> (numeric nonzero is true)
//   msg                       note              -> (print note; does not touch test state)
class AssertOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& I) override {

        I.register_op("expect_eq", [](WoflangInterpreter& I){
            if (I.stack.size() < 2) throw std::runtime_error("expect_eq: need actual expected");
            auto expected = I.stack.back(); I.stack.pop_back();
            auto actual   = I.stack.back(); I.stack.pop_back();

            if (actual.is_numeric() && expected.is_numeric()){
                double a = actual.as_numeric();
                double e = expected.as_numeric();
                if (a != e){
                    throw std::runtime_error("expect_eq failed: got " + std::to_string(a) +
                                             ", expected " + std::to_string(e));
                }
                return;
            }
            if ((actual.type == WofType::String || actual.type == WofType::Symbol) &&
                (expected.type == WofType::String || expected.type == WofType::Symbol)) {
                std::string a = std::get<std::string>(actual.value);
                std::string e = std::get<std::string>(expected.value);
                if (a != e){
                    throw std::runtime_error("expect_eq failed: got \"" + a + "\" != \"" + e + "\"");
                }
                return;
            }
            throw std::runtime_error("expect_eq: unsupported types");
        });

        I.register_op("expect_approx", [](WoflangInterpreter& I){
            if (I.stack.size() < 3) throw std::runtime_error("expect_approx: need actual expected tol");
            auto tolV = I.stack.back(); I.stack.pop_back();
            auto expV = I.stack.back(); I.stack.pop_back();
            auto actV = I.stack.back(); I.stack.pop_back();
            double tol = as_num(tolV, "expect_approx");
            double exp = as_num(expV, "expect_approx");
            double act = as_num(actV, "expect_approx");
            if (!(std::isfinite(tol) && tol >= 0.0)) throw std::runtime_error("expect_approx: bad tol");
            if (std::isnan(act) || std::isnan(exp) || std::fabs(act-exp) > tol){
                throw std::runtime_error("expect_approx failed: got " + std::to_string(act) +
                                         ", expected " + std::to_string(exp) +
                                         " (tol " + std::to_string(tol) + ")");
            }
        });

        I.register_op("expect_true", [](WoflangInterpreter& I){
            if (I.stack.empty()) throw std::runtime_error("expect_true: need cond");
            auto v = I.stack.back(); I.stack.pop_back();
            double cond = as_num(v, "expect_true");
            if (cond == 0.0) throw std::runtime_error("expect_true failed: condition is false (0)");
        });

        I.register_op("note", [](WoflangInterpreter& I){
            if (I.stack.empty()) throw std::runtime_error("note: need message");
            auto m = I.stack.back(); I.stack.pop_back();
            std::string s = as_str(m, "note");
            // stdout is fine for notes
            std::cout << "[NOTE] " << s << std::endl;
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::AssertOpsPlugin plugin;
    plugin.register_ops(interp);
}
