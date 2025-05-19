#include "../../src/core/woflang.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

class MarkovSuggestPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("suggest_math", [](WoflangInterpreter& interp) {
            // Demo: just output a random suggestion
            std::vector<std::string> sugg = {
                "Try: X X +", "Try: pi * radius radius *", "Try: a b + c +", "Try: X X *", "Try: sqrt Y"
            };
            int idx = std::rand() % sugg.size();
            std::cout << "[Markov Suggest] " << sugg[idx] << std::endl;
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static MarkovSuggestPlugin plugin;
    plugin.register_ops(interp);
}
