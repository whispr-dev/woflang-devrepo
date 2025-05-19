#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>

static std::vector<std::string> repl_history;

class ReplHistoryCommandPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("add_history", [](WoflangInterpreter& interp) {
            if (!interp.stack.empty()) {
                auto v = interp.stack.back(); interp.stack.pop_back();
                if (v.type == WofType::String || v.type == WofType::Symbol) {
                    repl_history.push_back(v.value.type == WofType::String ? std::get<std::string>(v.value.value) : "");
                }
            }
        });
        interp.register_op("show_history", [](WoflangInterpreter&) {
            std::cout << "REPL History:\n";
            for (size_t i = 0; i < repl_history.size(); ++i)
                std::cout << i << ": " << repl_history[i] << "\n";
        });
        interp.register_op("clear_history", [](WoflangInterpreter&) {
            repl_history.clear();
            std::cout << "REPL history cleared.\n";
        });
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static ReplHistoryCommandPlugin plugin;
    plugin.register_ops(interp);
}
