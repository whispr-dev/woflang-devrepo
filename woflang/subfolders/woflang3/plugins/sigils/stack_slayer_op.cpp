#include "../../src/core/woflang.hpp"
#include <iostream>

class StackSlayerOpPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("stack_slayer", [](WoflangInterpreter& interp) {
            std::cout << "☠️  The void has claimed your stack! (All items erased)" << std::endl;
            interp.clear_stack();
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static StackSlayerOpPlugin plugin;
    plugin.register_ops(interp);
}
