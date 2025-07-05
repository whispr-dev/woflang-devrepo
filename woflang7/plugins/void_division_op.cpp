// ==================================================
// FIXED: void_division_op.cpp
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <limits>

namespace woflang {

class VoidDivisionOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("void_division", [](std::stack<WofValue>& stack) {
            std::cout << "⚠️  FORBIDDEN OPERATION DETECTED ⚠️\n";
            std::cout << "Attempting to divide by the void...\n";
            
            if (stack.size() < 2) {
                std::cout << "The void requires a sacrifice.\n";
                return;
            }
            
            auto divisor = stack.top(); stack.pop();
            auto dividend = stack.top(); stack.pop();
            
            std::cout << "Dividing " << dividend.to_string() 
                     << " by the essence of nothingness...\n";
            
            // The void consumes all
            while (!stack.empty()) stack.pop();
            
            // But leaves behind infinity
            stack.push(WofValue(std::numeric_limits<double>::infinity()));
            
            std::cout << "The operation succeeds. Infinity remains.\n";
            std::cout << "You have gazed into the abyss.\n";
        });
        
        interp.register_op("/0", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "Even the void requires something to consume.\n";
                return;
            }
            
            auto value = stack.top(); stack.pop();
            
            std::cout << "÷0: " << value.to_string() << " → ∞\n";
            stack.push(WofValue(std::numeric_limits<double>::infinity()));
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::VoidDivisionOpsPlugin plugin;
    plugin.register_ops(interp);
}