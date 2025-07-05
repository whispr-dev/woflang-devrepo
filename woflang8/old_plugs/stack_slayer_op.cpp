// ==================================================
// FIXED: stack_slayer_op.cpp
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <thread>
#include <chrono>

namespace woflang {

class StackSlayerOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("stack_slayer", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "The Stack Slayer finds nothing to slay.\n";
                return;
            }
            
            std::cout << "⚔️  THE STACK SLAYER AWAKENS! ⚔️\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            size_t victims = stack.size();
            
            // Dramatically clear the stack
            for (size_t i = 0; i < victims; ++i) {
                std::cout << "💀 ";
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            std::cout << "\n";
            
            while (!stack.empty()) stack.pop();
            
            std::cout << "The Stack Slayer has claimed " << victims 
                     << " victims. The stack lies empty.\n";
        });
        
        interp.register_op("resurrect", [](std::stack<WofValue>& stack) {
            std::cout << "✨ Attempting resurrection ritual...\n";
            
            // Resurrect with mystical values
            stack.push(WofValue(3.14159));  // π
            stack.push(WofValue(2.71828));  // e
            stack.push(WofValue(1.61803));  // φ (golden ratio)
            
            std::cout << "Three sacred constants have risen from the void.\n";
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::StackSlayerOpsPlugin plugin;
    plugin.register_ops(interp);
}
