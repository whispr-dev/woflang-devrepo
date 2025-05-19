#include "../../src/core/woflang.hpp"
#include <iostream>

// Simple linear solver (for 2 X = 4)
class SymbolicSolveLinearPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("solve_linear", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 4) return;
            auto rhs = interp.stack.back(); interp.stack.pop_back();
            auto eq = interp.stack.back(); interp.stack.pop_back();
            auto var = interp.stack.back(); interp.stack.pop_back();
            auto coeff = interp.stack.back(); interp.stack.pop_back();

            if (coeff.type == WofType::Integer && eq.type == WofType::String && std::get<std::string>(eq.value) == "="
                && var.type == WofType::Symbol && rhs.type == WofType::Integer) {
                int64_t result = std::get<int64_t>(rhs.value) / std::get<int64_t>(coeff.value);
                std::cout << std::get<std::string>(var.value) << " = " << result << "\n";
                interp.stack.emplace_back(result);
            } else {
                std::cout << "[solve_linear] Could not solve; stack state unchanged.\n";
                interp.stack.push_back(coeff);
                interp.stack.push_back(var);
                interp.stack.push_back(eq);
                interp.stack.push_back(rhs);
            }
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static SymbolicSolveLinearPlugin plugin;
    plugin.register_ops(interp);
}
