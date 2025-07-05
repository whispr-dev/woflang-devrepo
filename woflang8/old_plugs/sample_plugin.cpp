// ==================================================
// FIXED: sample_plugin.cpp
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>

namespace woflang {

class SamplePlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("plugin_magic", [](std::stack<WofValue>&) {
            std::cout << "✨ Hello from plugin!\n";
        });
        
        interp.register_op("sample_test", [](std::stack<WofValue>& stack) {
            stack.push(WofValue(42.0));
            std::cout << "🎯 Sample plugin test - pushed 42\n";
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::SamplePlugin plugin;
    plugin.register_ops(interp);
}