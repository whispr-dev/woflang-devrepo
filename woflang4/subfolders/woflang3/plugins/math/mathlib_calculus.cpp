#include "../../src/core/woflang.hpp"
#include <cmath>

// Simple calculus ops (derivative, integral: stubs if you had logic, else expand!)
class MathlibCalculusPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("derivative", [](WoflangInterpreter& interp) {
            // Dummy: Real implementation would take a function representation!
            std::cout << "[derivative] Not implemented in demo—extend as in your original!\n";
        });
        interp.register_op("integral", [](WoflangInterpreter& interp) {
            std::cout << "[integral] Not implemented in demo—extend as in your original!\n";
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static MathlibCalculusPlugin plugin;
    plugin.register_ops(interp);
}
