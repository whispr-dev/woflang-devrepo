#include "../../src/core/woflang.hpp"
#include <cmath>

// Exponential and log ops
class MathlibExponentialsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("exp", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) throw std::runtime_error("Stack underflow on exp");
            auto x = interp.stack.back(); interp.stack.pop_back();
            if (x.type == WofType::Double)
                interp.stack.emplace_back(std::exp(std::get<double>(x.value)));
            else if (x.type == WofType::Integer)
                interp.stack.emplace_back(std::exp(static_cast<double>(std::get<int64_t>(x.value))));
            else
                throw std::runtime_error("Type error on exp");
        });
        interp.register_op("ln", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) throw std::runtime_error("Stack underflow on ln");
            auto x = interp.stack.back(); interp.stack.pop_back();
            if (x.type == WofType::Double)
                interp.stack.emplace_back(std::log(std::get<double>(x.value)));
            else if (x.type == WofType::Integer)
                interp.stack.emplace_back(std::log(static_cast<double>(std::get<int64_t>(x.value))));
            else
                throw std::runtime_error("Type error on ln");
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static MathlibExponentialsPlugin plugin;
    plugin.register_ops(interp);
}
