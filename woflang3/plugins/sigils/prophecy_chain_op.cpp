#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>

static std::vector<std::string> prophecy_chain;

class ProphecyChainOpPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("prophecy", [](WoflangInterpreter&) {
            std::vector<std::string> prophecies = {
                "A stack unbalanced is a prophecy unfulfilled.",
                "Beware the glyph echoing twice.",
                "The void grows with each lost symbol."
            };
            int idx = std::rand() % prophecies.size();
            std::string msg = prophecies[idx];
            prophecy_chain.push_back(msg);
            std::cout << "[Prophecy] " << msg << std::endl;
        });
        interp.register_op("prophecy_chain", [](WoflangInterpreter&) {
            std::cout << "🔗  Prophecy Chain:\n";
            for (auto& p : prophecy_chain) std::cout << "  " << p << "\n";
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static ProphecyChainOpPlugin plugin;
    plugin.register_ops(interp);
}
