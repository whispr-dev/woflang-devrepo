// ==================================================
// FIXED: prophecy_op.cpp
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <vector>

namespace woflang {

class ProphecyOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("prophecy", [](std::stack<WofValue>& stack) {
            static const std::vector<std::string> prophecies = {
                "The stack shall overflow with wisdom.",
                "A great recursion approaches.",
                "Beware the null pointer of destiny.",
                "The garbage collector comes for us all.",
                "In the end, all returns to void.",
                "The algorithm of fate is O(∞).",
                "Your code compiles, but at what cost?",
                "The segfault was within you all along.",
                "Stack and heap, forever in balance.",
                "The undefined behavior defines us."
            };
            
            static std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<> dis(0, prophecies.size() - 1);
            
            std::cout << "\n🔮 The Oracle speaks:\n";
            std::cout << "   \"" << prophecies[dis(gen)] << "\"\n\n";
            
            // Push a mystical value
            stack.push(WofValue(42.0));
        });
        
        interp.register_op("oracle", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "The Oracle requires an offering.\n";
                return;
            }
            
            auto offering = stack.top(); stack.pop();
            
            std::cout << "The Oracle contemplates your offering of " 
                     << offering.to_string() << "...\n";
            
            // Divine the future based on the offering
            double divination = offering.as_numeric();
            divination = std::sin(divination) * std::cos(divination * 3.14159);
            
            std::cout << "The Oracle reveals: " << divination << "\n";
            stack.push(WofValue(divination));
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::ProphecyOpsPlugin plugin;
    plugin.register_ops(interp);
}