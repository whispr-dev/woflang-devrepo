// ==================================================
// FIXED: quantum_ops.cpp - Properly integrated
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <complex>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>

namespace woflang {

// Quantum state representation using WofValue extensions
class QuantumState {
public:
    std::vector<std::complex<double>> amplitudes;
    
    QuantumState(const std::vector<std::complex<double>>& amps) : amplitudes(amps) {}
    
    // |0⟩ state
    static QuantumState zero() {
        return QuantumState({std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0)});
    }
    
    // |1⟩ state  
    static QuantumState one() {
        return QuantumState({std::complex<double>(0.0, 0.0), std::complex<double>(1.0, 0.0)});
    }
    
    // Superposition state
    static QuantumState superposition() {
        double inv_sqrt2 = 1.0 / std::sqrt(2.0);
        return QuantumState({std::complex<double>(inv_sqrt2, 0.0), std::complex<double>(inv_sqrt2, 0.0)});
    }
};

class QuantumOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // Create quantum states
        interp.register_op("|0⟩", [](std::stack<WofValue>& stack) {
            stack.push(WofValue(0.0)); // Represent |0⟩ as 0
            std::cout << "⚛️ |0⟩ quantum state created\n";
        });
        
        interp.register_op("|1⟩", [](std::stack<WofValue>& stack) {
            stack.push(WofValue(1.0)); // Represent |1⟩ as 1
            std::cout << "⚛️ |1⟩ quantum state created\n";
        });
        
        // Hadamard gate
        interp.register_op("H", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "Error: H gate requires a qubit state\n";
                return;
            }
            
            auto qubit = stack.top(); stack.pop();
            
            if (qubit.is_numeric()) {
                double val = qubit.as_numeric();
                if (val == 0.0) {
                    stack.push(WofValue(0.5)); // |0⟩ → |+⟩ (superposition)
                    std::cout << "⚛️ Hadamard: |0⟩ → |+⟩ (superposition)\n";
                } else if (val == 1.0) {
                    stack.push(WofValue(-0.5)); // |1⟩ → |−⟩ (negative superposition)
                    std::cout << "⚛️ Hadamard: |1⟩ → |−⟩ (negative superposition)\n";
                } else {
                    stack.push(WofValue(val * 0.707)); // Generic superposition
                    std::cout << "⚛️ Hadamard applied to superposition state\n";
                }
            } else {
                stack.push(qubit);
                std::cout << "⚛️ Hadamard gate error: Not a valid qubit state\n";
            }
        });
        
        // Pauli-X gate (bit flip)
        interp.register_op("X", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "Error: X gate requires a qubit state\n";
                return;
            }
            
            auto qubit = stack.top(); stack.pop();
            
            if (qubit.is_numeric()) {
                double val = qubit.as_numeric();
                if (val == 0.0) {
                    stack.push(WofValue(1.0)); // |0⟩ → |1⟩
                    std::cout << "🔄 Pauli-X: |0⟩ → |1⟩\n";
                } else if (val == 1.0) {
                    stack.push(WofValue(0.0)); // |1⟩ → |0⟩
                    std::cout << "🔄 Pauli-X: |1⟩ → |0⟩\n";
                } else {
                    stack.push(WofValue(1.0 - val)); // Flip superposition
                    std::cout << "🔄 Pauli-X applied to superposition\n";
                }
            } else {
                stack.push(qubit);
                std::cout << "🔄 X gate error: Not a valid qubit state\n";
            }
        });
        
        // Pauli-Y gate
        interp.register_op("Y", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "Error: Y gate requires a qubit state\n";
                return;
            }
            
            auto qubit = stack.top(); stack.pop();
            
            if (qubit.is_numeric()) {
                double val = qubit.as_numeric();
                // Y gate introduces complex phase - simplified representation
                stack.push(WofValue(-val + 1.0)); // Simplified Y operation
                std::cout << "🌀 Pauli-Y gate applied (with phase)\n";
            } else {
                stack.push(qubit);
                std::cout << "🌀 Y gate error: Not a valid qubit state\n";
            }
        });
        
        // Pauli-Z gate (phase flip)
        interp.register_op("Z", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "Error: Z gate requires a qubit state\n";
                return;
            }
            
            auto qubit = stack.top(); stack.pop();
            
            if (qubit.is_numeric()) {
                double val = qubit.as_numeric();
                if (val == 1.0) {
                    stack.push(WofValue(-1.0)); // |1⟩ → -|1⟩
                    std::cout << "⚡ Pauli-Z: |1⟩ → -|1⟩ (phase flip)\n";
                } else {
                    stack.push(qubit); // |0⟩ unchanged
                    std::cout << "⚡ Pauli-Z: |0⟩ unchanged\n";
                }
            } else {
                stack.push(qubit);
                std::cout << "⚡ Z gate error: Not a valid qubit state\n";
            }
        });
        
        // Quantum measurement
        interp.register_op("measure", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "Error: Measurement requires a qubit state\n";
                return;
            }
            
            auto qubit = stack.top(); stack.pop();
            
            if (qubit.is_numeric()) {
                double val = qubit.as_numeric();
                
                // Calculate probabilities (simplified)
                double prob_0, prob_1;
                if (val == 0.0) {
                    prob_0 = 1.0; prob_1 = 0.0;
                } else if (val == 1.0) {
                    prob_0 = 0.0; prob_1 = 1.0;
                } else {
                    // Superposition - equal probabilities for simplicity
                    prob_0 = 0.5; prob_1 = 0.5;
                }
                
                // Random measurement
                static std::random_device rd;
                static std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.0, 1.0);
                
                double rand_val = dis(gen);
                int result = (rand_val < prob_0) ? 0 : 1;
                
                std::cout << "🔬 Quantum measurement result: |" << result << "⟩\n";
                std::cout << "   Probabilities: |0⟩=" << std::fixed << std::setprecision(1) 
                         << prob_0 * 100 << "% |1⟩=" << prob_1 * 100 << "%\n";
                
                stack.push(WofValue(static_cast<double>(result)));
            } else {
                stack.push(qubit);
                std::cout << "🔬 Measurement error: Not a valid qubit state\n";
            }
        });
        
        // Show quantum state
        interp.register_op("show", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "Error: State display requires a qubit state\n";
                return;
            }
            
            auto qubit = stack.top(); // Don't pop, just show
            
            if (qubit.is_numeric()) {
                double val = qubit.as_numeric();
                std::cout << "🔮 Qubit state: ";
                
                if (val == 0.0) {
                    std::cout << "|0⟩\n";
                } else if (val == 1.0) {
                    std::cout << "|1⟩\n";
                } else if (val == 0.5) {
                    std::cout << "|+⟩ = (|0⟩ + |1⟩)/√2\n";
                } else if (val == -0.5) {
                    std::cout << "|−⟩ = (|0⟩ - |1⟩)/√2\n";
                } else {
                    std::cout << "Superposition state (α=" << val << ")\n";
                }
            } else {
                std::cout << "🔮 Not a valid quantum state\n";
            }
        });
        
        // Quantum teleportation
        interp.register_op("teleport", [](std::stack<WofValue>& stack) {
            std::cout << "🌌 Quantum teleportation protocol initiated!\n";
            std::cout << "   'Spooky action at a distance' - Einstein\n";
            std::cout << "   📡 Entangled particles prepared...\n";
            std::cout << "   🔄 Bell measurement performed...\n";
            std::cout << "   ✨ Quantum state teleported successfully!\n";
            
            stack.push(WofValue(1.0)); // Success indicator
        });
        
        // Create Bell state (entangled pair)
        interp.register_op("bell", [](std::stack<WofValue>& stack) {
            std::cout << "🔗 Creating Bell state |Φ+⟩ = (|00⟩ + |11⟩)/√2\n";
            std::cout << "   Entangled particles generated! 🌟\n";
            
            // Push two entangled qubits (represented as correlated values)
            stack.push(WofValue(0.707)); // First entangled qubit
            stack.push(WofValue(0.707)); // Second entangled qubit
        });
        
        // Quantum interference
        interp.register_op("interfere", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                std::cout << "🌊 Interference requires two quantum states\n";
                return;
            }
            
            auto qubit2 = stack.top(); stack.pop();
            auto qubit1 = stack.top(); stack.pop();
            
            if (qubit1.is_numeric() && qubit2.is_numeric()) {
                double interference = qubit1.as_numeric() + qubit2.as_numeric();
                stack.push(WofValue(interference));
                std::cout << "🌊 Quantum interference: " << interference << "\n";
            } else {
                stack.push(qubit1);
                stack.push(qubit2);
                std::cout << "🌊 Interference error: Invalid quantum states\n";
            }
        });
        
        // Quantum tutorial
        interp.register_op("quantum_tutorial", [](std::stack<WofValue>&) {
            std::cout << "=== Quantum Computing Tutorial ===\n\n";
            std::cout << "🔬 Quantum Bits (Qubits):\n";
            std::cout << "   Unlike classical bits (0 or 1), qubits can be in superposition\n";
            std::cout << "   |ψ⟩ = α|0⟩ + β|1⟩  where |α|² + |β|² = 1\n\n";
            
            std::cout << "🚪 Quantum Gates:\n";
            std::cout << "   H  - Hadamard gate (creates superposition)\n";
            std::cout << "   X  - Pauli-X gate (bit flip)\n";
            std::cout << "   Y  - Pauli-Y gate (bit + phase flip)\n";
            std::cout << "   Z  - Pauli-Z gate (phase flip)\n\n";
            
            std::cout << "🔬 Operations:\n";
            std::cout << "   |0⟩, |1⟩     - Create basis states\n";
            std::cout << "   measure     - Collapse superposition\n";
            std::cout << "   show        - Display current state\n";
            std::cout << "   bell        - Create entangled pair\n";
            std::cout << "   teleport    - Quantum teleportation\n";
            std::cout << "   interfere   - Quantum interference\n\n";
            
            std::cout << "Try: |0⟩ H show measure\n";
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::QuantumOpsPlugin plugin;
    plugin.register_ops(interp);
}