#include "../../src/core/woflang.hpp"
#include <iostream>
#include <cstdlib>

class OmegaOpPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("omega", [](WoflangInterpreter&) {
            std::cout << "Ω  All cycles end. The interpreter closes. Until next session, fren!" << std::endl;
            std::exit(0);
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static OmegaOpPlugin plugin;
    plugin.register_ops(interp);
}
