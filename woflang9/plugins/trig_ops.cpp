// plugins/trig_ops.cpp
#ifndef WOFLANG_PLUGIN_EXPORT
#  ifdef _WIN32
#    define WOFLANG_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#  else
#    define WOFLANG_PLUGIN_EXPORT extern "C"
#  endif
#endif

#include "core/woflang.hpp"
#include <cmath>
#include <numbers>
#include <stdexcept>
#include <stack>

namespace woflang {

static inline double deg2rad(double d) { return d * std::numbers::pi_v<double> / 180.0; }
static inline double rad2deg(double r) { return r * 180.0 / std::numbers::pi_v<double>; }

static inline double need_num(const WofValue& v, const char* op){
    if (!v.is_numeric()) throw std::runtime_error(std::string(op)+": numeric required");
    return v.as_numeric();
}

class TrigOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& I) override {
        I.register_op("sin", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("sin: stack underflow");
            auto a = S.top(); S.pop();
            S.push(WofValue(std::sin(need_num(a,"sin"))));
        });
        I.register_op("cos", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("cos: stack underflow");
            auto a = S.top(); S.pop();
            S.push(WofValue(std::cos(need_num(a,"cos"))));
        });
        I.register_op("tan", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("tan: stack underflow");
            auto a = S.top(); S.pop();
            S.push(WofValue(std::tan(need_num(a,"tan"))));
        });

        I.register_op("asin", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("asin: stack underflow");
            auto a = S.top(); S.pop();
            double v = need_num(a,"asin");
            if (v < -1.0 || v > 1.0) throw std::runtime_error("asin: domain [-1,1]");
            S.push(WofValue(std::asin(v)));
        });
        I.register_op("acos", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("acos: stack underflow");
            auto a = S.top(); S.pop();
            double v = need_num(a,"acos");
            if (v < -1.0 || v > 1.0) throw std::runtime_error("acos: domain [-1,1]");
            S.push(WofValue(std::acos(v)));
        });
        I.register_op("atan", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("atan: stack underflow");
            auto a = S.top(); S.pop();
            S.push(WofValue(std::atan(need_num(a,"atan"))));
        });
        // y x atan2
        I.register_op("atan2", [](std::stack<WofValue>& S){
            if (S.size() < 2) throw std::runtime_error("atan2: stack underflow");
            auto x = S.top(); S.pop();
            auto y = S.top(); S.pop();
            S.push(WofValue(std::atan2(need_num(y,"atan2"), need_num(x,"atan2"))));
        });

        I.register_op("sinh", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("sinh: stack underflow");
            auto a = S.top(); S.pop();
            S.push(WofValue(std::sinh(need_num(a,"sinh"))));
        });
        I.register_op("cosh", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("cosh: stack underflow");
            auto a = S.top(); S.pop();
            S.push(WofValue(std::cosh(need_num(a,"cosh"))));
        });
        I.register_op("tanh", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("tanh: stack underflow");
            auto a = S.top(); S.pop();
            S.push(WofValue(std::tanh(need_num(a,"tanh"))));
        });

        I.register_op("deg2rad", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("deg2rad: stack underflow");
            auto d = S.top(); S.pop();
            S.push(WofValue(deg2rad(need_num(d,"deg2rad"))));
        });
        I.register_op("rad2deg", [](std::stack<WofValue>& S){
            if (S.size() < 1) throw std::runtime_error("rad2deg: stack underflow");
            auto r = S.top(); S.pop();
            S.push(WofValue(rad2deg(need_num(r,"rad2deg"))));
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::TrigOpsPlugin plugin;
    plugin.register_ops(interp);
}
