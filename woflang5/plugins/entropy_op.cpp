#include "../src/core/woflang.hpp"
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

namespace woflang {

class EntropyOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("entropy", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "The void has no entropy. Only chaos remains.\n";
                return;
            }
            
            // Calculate Shannon entropy of the stack
            std::map<std::string, int> counts;
            double total = 0;
            
            for (const auto& val : interp.stack) {
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
            
            interp.push(WofValue(entropy));
        });
        
        interp.register_op("chaos", [](WoflangInterpreter& interp) {
            static std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
            
            // Generate chaotic values
            std::uniform_real_distribution<> dis(0.0, 1.0);
            double chaos_value = dis(gen);
            
            std::cout << "From chaos, order emerges: " << chaos_value << "\n";
            
            // Randomly shuffle the stack
            if (interp.stack.size() > 1) {
                std::shuffle(interp.stack.begin(), interp.stack.end(), gen);
                std::cout << "The stack has been touched by chaos.\n";
            }
            
            interp.push(WofValue(chaos_value));
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::EntropyOpsPlugin plugin;
    plugin.register_ops(interp);
}