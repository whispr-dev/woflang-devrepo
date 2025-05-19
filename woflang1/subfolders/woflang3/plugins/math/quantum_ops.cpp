#include "../../src/core/woflang.hpp"
#include <iostream>
#include <random>

// Simulates qubit states and a few gates, stack holds 0 or 1 for simplicity
class QuantumOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("|ψ⟩", [](WoflangInterpreter& interp) {
            // Pushes superposition (random 0/1) for demo
            interp.stack.emplace_back((std::rand() % 2) ? 1 : 0);
            std::cout << "|ψ⟩: Superposed (random qubit pushed)\n";
        });
        interp.register_op("H", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) { std::cout << "H: need qubit\n"; return; }
            // Hadamard gate: always returns 0 or 1 with 50% chance
            interp.stack.pop_back();
            interp.stack.emplace_back((std::rand() % 2) ? 1 : 0);
            std::cout << "H: Hadamard applied (randomized qubit)\n";
        });
        interp.register_op("X", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) return;
            auto q = interp.stack.back(); interp.stack.pop_back();
            if (q.type == WofType::Integer)
                interp.stack.emplace_back(std::get<int64_t>(q.value) == 0 ? 1 : 0);
            else std::cout << "X: Qubit only\n";
        });
        interp.register_op("measure", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) return;
            auto q = interp.stack.back(); interp.stack.pop_back();
            std::cout << "Measured: " << (q.type == WofType::Integer ? std::get<int64_t>(q.value) : -1) << std::endl;
        });
        // Add more quantum gates as you wish!
    }
};

WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static QuantumOpsPlugin plugin;
    plugin.register_ops(interp);
}
