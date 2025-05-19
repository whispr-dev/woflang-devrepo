#include "../../src/core/woflang.hpp"
#include <iostream>

class ReplEggCommandPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("egg", [](WoflangInterpreter&) {
            std::cout << "[Easter Egg] A little joy for your stack!" << std::endl;
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static ReplEggCommandPlugin plugin;
    plugin.register_ops(interp);
}
