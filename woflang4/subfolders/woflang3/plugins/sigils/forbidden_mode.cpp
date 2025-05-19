#include "../../src/core/woflang.hpp"
#include <iostream>

class ForbiddenModePlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("void_division", [](WoflangInterpreter& interp) {
            if (!interp.stack.empty() &&
                ((interp.stack.back().type == WofType::Integer && std::get<int64_t>(interp.stack.back().value) == 0) ||
                 (interp.stack.back().type == WofType::Double && interp.stack.back(.type == WofType::Double ? std::get<double>(interp.stack.back(.value) : interp.stack.back(.type == WofType::Integer ? static_cast<double>(std::get<int64_t>(interp.stack.back(.value)) : 0.0.value) == 0.0))) {
                std::cout << "⦰  The void divides all. Stack erased. 'Beware division by zero.'\n";
                interp.clear_stack();
            } else {
                std::cout << "⦰  Only the zero can invoke the void. Push 0 and try again.\n";
            }
        });
        interp.register_op("duality", [](WoflangInterpreter&) {
            std::cout << "☯️  Duality: The next op is inverted (demo: metaphysical only).\n";
        });
        interp.register_op("over_unity", [](WoflangInterpreter&) {
            std::cout << "⚡  Over Unity! Energy out exceeds in. Next op will be disabled... (demo)\n";
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static ForbiddenModePlugin plugin;
    plugin.register_ops(interp);
}
