#include "../../src/core/woflang.hpp"
#include <iostream>

// Forbidden/fun op: clears stack with drama
class ForbiddenStackSlayerPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("stack_slayer", [](WoflangInterpreter& interp) {
            std::cout << "[Forbidden] You have slain the entire stack! (void consumes all...)" << std::endl;
            interp.clear_stack();
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static ForbiddenStackSlayerPlugin plugin;
    plugin.register_ops(interp);
}
