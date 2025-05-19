#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>

class ProphecyOpPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("prophecy", [](WoflangInterpreter& interp) {
            // Optional: Only allow in REPL mode (could pass REPL state/context in real build)
            std::vector<std::string> prophecies = {
                "In the glyph’s shadow, your stack’s fate is sealed.",
                "Beware: The next push may tip the void.",
                "The stack will echo your intent, not your command.",
                "A silent glyph is the most powerful of all."
            };
            int idx = std::rand() % prophecies.size();
            std::cout << "[Prophecy] " << prophecies[idx] << std::endl;
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static ProphecyOpPlugin plugin;
    plugin.register_ops(interp);
}
