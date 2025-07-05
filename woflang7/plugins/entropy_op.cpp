// ==================================================
// FIXED: entropy_op.cpp
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <map>

namespace woflang {

class EntropyOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("entropy", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "The void has no entropy. Only chaos remains.\n";
                return;
            }
            
            // Calculate Shannon entropy of the stack
            std::map<std::string, int> counts;
            double total = 0;
            
            // Copy stack to vector to analyze without destroying
            std::vector<WofValue> values;
            std::stack<WofValue> temp_stack = stack;
            while (!temp_stack.empty()) {
                values.push_back(temp_stack.top());
                temp_stack.pop();
            }
            
            for (const auto& val : values) {
                counts[val.to_string()]++;
                total++;
            }
            
            double entropy = 0.0;
            for (const auto& [_, count] : counts) {
                double p = count / total;
                entropy -= p * std::log2(p);
            }
            
            std::cout << "Stack entropy: " << entropy << " bits\n";
            std::cout << "The universe tends toward maximum entropy...\n";
            
            stack.push(WofValue(entropy));
        });
        
        interp.register_op("chaos", [](std::stack<WofValue>& stack) {
            static std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
            
            // Generate chaotic values
            std::uniform_real_distribution<> dis(0.0, 1.0);
            double chaos_value = dis(gen);
            
            std::cout << "From chaos, order emerges: " << chaos_value << "\n";
            
            // Randomly shuffle the stack
            if (stack.size() > 1) {
                std::vector<WofValue> values;
                while (!stack.empty()) {
                    values.push_back(stack.top());
                    stack.pop();
                }
                std::shuffle(values.begin(), values.end(), gen);
                for (auto& val : values) {
                    stack.push(val);
                }
                std::cout << "The stack has been touched by chaos.\n";
            }
            
            stack.push(WofValue(chaos_value));
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::EntropyOpsPlugin plugin;
    plugin.register_ops(interp);
}