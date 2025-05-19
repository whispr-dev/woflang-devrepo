#include "../../src/core/woflang.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

class WofMarkovMathSuggestionsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("markov_suggest", [](WoflangInterpreter& interp) {
            std::vector<std::string> sugg = {
                "Try: X X +", "Try: pi * radius radius *", "Try: X X *", "Try: sum i = 1 to N"
            };
            int idx = std::rand() % sugg.size();
            std::cout << "[Markov Suggestion] " << sugg[idx] << std::endl;
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static WofMarkovMathSuggestionsPlugin plugin;
    plugin.register_ops(interp);
}
