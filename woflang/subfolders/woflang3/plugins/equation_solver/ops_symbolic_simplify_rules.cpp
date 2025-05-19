#include "../../src/core/woflang.hpp"
#include <iostream>

// Simple pattern-based symbolic simplification rules plugin
class SymbolicSimplifyRulesPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("simplify_sum", [](WoflangInterpreter& interp) {
            // Rule: X + X -> 2 * X
            if (interp.stack.size() < 3) return;
            auto c = interp.stack.back(); interp.stack.pop_back();
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();

            if (a.type == WofType::Symbol && b.type == WofType::Symbol && a.value.type == WofType::String ? std::get<std::string>(a.value.value) : "" == b.value.type == WofType::String ? std::get<std::string>(b.value.value) : ""
                && c.type == WofType::String && c.value.type == WofType::String ? std::get<std::string>(c.value.value) : "" == "+") {
                interp.stack.emplace_back(2);
                interp.stack.push_back(a);
                interp.stack.emplace_back("*", WofType::String);
            } else {
                interp.stack.push_back(a);
                interp.stack.push_back(b);
                interp.stack.push_back(c);
            }
        });

        // Add more: X*1, X+0, etc.
        interp.register_op("simplify_mul_one", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 3) return;
            auto c = interp.stack.back(); interp.stack.pop_back();
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();

            // Rule: X * 1 => X
            if (a.type == WofType::Symbol && b.type == WofType::Integer && std::get<int64_t>(b.value) == 1 &&
                c.type == WofType::String && c.value.type == WofType::String ? std::get<std::string>(c.value.value) : "" == "*") {
                interp.stack.push_back(a);
            } else {
                interp.stack.push_back(a);
                interp.stack.push_back(b);
                interp.stack.push_back(c);
            }
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static SymbolicSimplifyRulesPlugin plugin;
    plugin.register_ops(interp);
}
