#include "../../src/core/woflang.hpp"

// Physics constants plugin
class PhysicsConstantsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("c", [](WoflangInterpreter& interp) {
            // Speed of light in m/s
            interp.stack.emplace_back(299792458.0);
        });
        interp.register_op("G", [](WoflangInterpreter& interp) {
            // Gravitational constant
            interp.stack.emplace_back(6.67430e-11);
        });
        interp.register_op("h", [](WoflangInterpreter& interp) {
            // Planck's constant
            interp.stack.emplace_back(6.62607015e-34);
        });
        interp.register_op("e_charge", [](WoflangInterpreter& interp) {
            // Elementary charge
            interp.stack.emplace_back(1.602176634e-19);
        });
        // Add more as in your original!
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static PhysicsConstantsPlugin plugin;
    plugin.register_ops(interp);
}
