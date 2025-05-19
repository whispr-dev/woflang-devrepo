#include "../../src/core/woflang.hpp"
#include <iostream>

// Register a plugin for math constants
class MathConstantsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("pi", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(3.14159265358979323846);
        });
        interp.register_op("e", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(2.71828182845904523536);
        });
        // Add more constants as needed...
    }
};

// Plugin export function (for Windows DLLs)
WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static MathConstantsPlugin plugin;
    plugin.register_ops(interp);
}
