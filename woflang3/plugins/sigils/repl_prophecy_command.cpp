#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>

class ReplProphecyCommandPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("prophesy", [](WoflangInterpreter&) {
            std::vector<std::string> prophecies = {
                "In the void, all stacks return to zero.",
                "A glyph unspoken is a stack unpushed.",
                "He who divides by zero will see the face of the stack void.",
                "All prophecy is self-fulfilling in woflang."
            };
            int idx = std::rand() % prophecies.size();
            std::cout << "[Prophecy] " << prophecies[idx] << "\n";
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static ReplProphecyCommandPlugin plugin;
    plugin.register_ops(interp);
}
