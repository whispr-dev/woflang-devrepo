#include "../../src/core/woflang.hpp"

// Modelica constants plugin (your own list can be much longer!)
class ModelicaConstantsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("pi_modelica", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(3.141592653589793);
        });
        interp.register_op("deg2rad", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(0.0174532925199433); // pi/180
        });
        interp.register_op("rad2deg", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(57.2957795130823); // 180/pi
        });
        // Add all your Modelica constants!
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static ModelicaConstantsPlugin plugin;
    plugin.register_ops(interp);
}
