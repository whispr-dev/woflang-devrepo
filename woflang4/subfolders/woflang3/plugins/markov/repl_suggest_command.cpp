#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>

class ReplSuggestCommandPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("suggest", [](WoflangInterpreter&) {
            // Could read from a real suggestion file in your real plugin!
            std::vector<std::string> suggestions = {
                "Try: 2 pi * r *",
                "Try: X X +",
                "Try: a b + c +",
                "Try: sum n = 1 to N"
            };
            int idx = std::rand() % suggestions.size();
            std::cout << "[Suggest] " << suggestions[idx] << "\n";
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static ReplSuggestCommandPlugin plugin;
    plugin.register_ops(interp);
}
