#include "../../src/core/woflang.hpp"
#include <iostream>

class OverUnityOpPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("over_unity", [](WoflangInterpreter&) {
            std::cout << "⚡  Over Unity! Energy out exceeds energy in. Next op will be disabled...\n";
            // Optional: set a global "disable-next-op" flag (advanced extension)
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static OverUnityOpPlugin plugin;
    plugin.register_ops(interp);
}
