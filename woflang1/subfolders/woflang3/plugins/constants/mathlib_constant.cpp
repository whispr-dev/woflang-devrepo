#include "../../src/core/woflang.hpp"
#include <cmath>

// Math constants plugin (pi, e, tau, phi, etc.)
class MathlibConstantsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("pi", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(3.14159265358979323846);
        });
        interp.register_op("e", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(2.71828182845904523536);
        });
        interp.register_op("tau", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(6.28318530717958647692);
        });
        interp.register_op("phi", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(1.61803398874989484820);
        });
        interp.register_op("sqrt2", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(1.41421356237309504880);
        });
        interp.register_op("ln2", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(0.69314718055994530941);
        });
        // Add more if you had them!
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static MathlibConstantsPlugin plugin;
    plugin.register_ops(interp);
}
