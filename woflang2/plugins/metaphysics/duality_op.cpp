#include "../../src/core/woflang.hpp"
#include <iostream>

class DualityOpPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // This is a playful version. To actually invert op semantics, you'd need interpreter hooks!
        interp.register_op("duality", [](WoflangInterpreter& interp) {
            std::cout << "☯️  The next op is inverted! (Demo: Inversion is metaphysical.)\n";
            // For full inversion: could toggle a global, or invert last op (advanced extension)
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static DualityOpPlugin plugin;
    plugin.register_ops(interp);
}
