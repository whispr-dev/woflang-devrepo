#include "../../src/core/woflang.hpp"
#include <iostream>

class EggOpPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("egg", [](WoflangInterpreter&) {
            std::cout << "🥚  You have discovered the Joy Egg! May your stack never underflow!" << std::endl;
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static EggOpPlugin plugin;
    plugin.register_ops(interp);
}
