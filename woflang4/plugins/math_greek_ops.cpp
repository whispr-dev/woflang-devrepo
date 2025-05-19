WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static MathGreekPlugin plugin;
    plugin.register_ops(interp);
}
quantum_ops.cpp (Fixed)
cpp#include "../../src/core/woflang.hpp"
#include <iostream>
#include <random>

// Simulates qubit states and a few gates, stack holds 0 or 1 for simplicity
class QuantumOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // Random number generator setup
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 1);
        
        interp.register_op("|ψ⟩", [&dist, &gen](WoflangInterpreter& interp) {
            // Pushes superposition (random 0/1) for demo
            interp.stack.emplace_back(dist(gen));
            std::cout << "|ψ⟩: Superposed (random qubit pushed)\n";
        });
        
        interp.register_op("H", [&dist, &gen](WoflangInterpreter& interp) {
            if (interp.stack.empty()) { 
                std::cout << "H: need qubit\n"; 
                return; 
            }
            // Hadamard gate: always returns 0 or 1 with 50% chance
            interp.stack.pop_back();
            interp.stack.emplace_back(dist(gen));
            std::cout << "H: Hadamard applied (randomized qubit)\n";
        });
        
        interp.register_op("X", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) return;
            
            auto q = interp.stack.back(); 
            interp.stack.pop_back();
            
            if (q.type == WofType::Integer) {
                int64_t val = std::get<int64_t>(q.value);
                interp.stack.emplace_back(val == 0 ? 1 : 0);
            } else {
                std::cout << "X: Qubit only\n";
                interp.stack.push_back(q); // Put it back if not integer
            }
        });
        
        interp.register_op("measure", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) return;
            
            auto q = interp.stack.back(); 
            interp.stack.pop_back();
            
            if (q.type == WofType::Integer) {
                std::cout << "Measured: " << std::get<int64_t>(q.value) << std::endl;
            } else {
                std::cout << "measure: Qubit only\n";
                interp.stack.push_back(q); // Put it back if not integer
            }
        });
        // Add more quantum gates as you wish!
    }
};



