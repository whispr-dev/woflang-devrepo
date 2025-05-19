#include "../../src/core/woflang.hpp"
#include <iostream>

class SigilMapOpPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("sigil_map", [](WoflangInterpreter&) {
            std::cout << "Sacred Sigils:\n"
                      << "prophecy (🔮): Cryptic stack fate message\n"
                      << "stack_slayer (☠️): Destroys the stack (forbidden)\n"
                      << "egg (🥚): Joy Easter Egg\n"
                      << "glyph_prophecy (🜄): Secret, full-moon only\n"
                      << "omega (Ω): Session ending\n"
                      << "sigil_map (🗺️): This map\n";
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static SigilMapOpPlugin plugin;
    plugin.register_ops(interp);
}
