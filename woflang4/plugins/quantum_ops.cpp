#include "../../src/core/woflang.hpp"
#include <iostream>
#include <complex>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>

namespace woflang {

/**
 * @brief Quantum state representation for qubit operations
 */
class QuantumState {
public:
    // Vector of complex amplitudes for basis states
    std::vector<std::complex<double>> amplitudes;
    
    // Create state from amplitudes
    explicit QuantumState(const std::vector<std::complex<double>>& amps) 
        : amplitudes(amps) {
        normalize();
    }
    
    // Default to |0⟩ state
    QuantumState() : amplitudes({1.0, 0.0}) {}
    
    // Check if the state is normalized
    [[nodiscard]] bool is_normalized() const {
        double sum = 0.0;
        for (const auto& amp : amplitudes) {
            sum += std::norm(amp);  // |amplitude|^2
        }
        return std::abs(sum - 1.0) < 1e-10;
    }
    
    // Normalize the state
    void normalize() {
        double norm_factor = 0.0;
        for (const auto& amp : amplitudes) {
            norm_factor += std::norm(amp);
        }
        
        norm_factor = std::sqrt(norm_factor);
        
        if (norm_factor > 1e-10) {  // Avoid division by zero
            for (auto& amp : amplitudes) {
                amp /= norm_factor;
            }
        }
    }
    
    // Apply single-qubit gate (2x2 matrix)
    void apply_gate(const std::vector<std::complex<double>>& matrix) {
        if (amplitudes.size() == 2 && matrix.size() == 4) {
            // Apply 2x2 matrix to single-qubit state
            std::complex<double> new_0 = matrix[0] * amplitudes[0] + matrix[1] * amplitudes[1];
            std::complex<double> new_1 = matrix[2] * amplitudes[0] + matrix[3] * amplitudes[1];
            
            amplitudes[0] = new_0;
            amplitudes[1] = new_1;
            
            // Ensure state remains normalized
            normalize();
        } else {
            throw std::runtime_error("Invalid gate application");
        }
    }
    
    // Get probability of measuring |0⟩
    [[nodiscard]] double prob_0() const {
        return std::norm(amplitudes[0]);
    }
    
    // Get probability of measuring |1⟩
    [[nodiscard]] double prob_1() const {
        return std::norm(amplitudes[1]);
    }
    
    // Convert state to string representation
    [[nodiscard]] std::string to_string() const {
        std::stringstream ss;
        
        double prob0 = prob_0();
        double prob1 = prob_1();
        
        // Simple case: pure |0⟩ or |1⟩
        if (prob0 > 0.999) {
            return "|0⟩";
        } else if (prob1 > 0.999) {
            return "|1⟩";
        }
        
        // For |+⟩ and |-⟩ states
        if (std::abs(prob0 - 0.5) < 0.01 && std::abs(prob1 - 0.5) < 0.01) {
            double phase = std::arg(amplitudes[1] / amplitudes[0]);
            if (std::abs(phase) < 0.01) {
                return "|+⟩";
            } else if (std::abs(phase - M_PI) < 0.01 || std::abs(phase + M_PI) < 0.01) {
                return "|-⟩";
            }
        }
        
        // General case: full state vector
        ss << amplitudes[0] << "|0⟩ + " << amplitudes[1] << "|1⟩";
        return ss.str();
    }
};

/**
 * @brief Convert between QuantumState and WofValue
 */
namespace quantum_helpers {
    // Convert QuantumState to WofValue
    WofValue state_to_wof(const QuantumState& state) {
        WofValue val(state.to_string(), WofType::Symbol);
        val.unit = "qubit";
        return val;
    }
    
    // Try to convert WofValue to QuantumState
    QuantumState wof_to_state(const WofValue& value) {
        if (value.type != WofType::Symbol || !value.unit || *value.unit != "qubit") {
            throw std::runtime_error("Not a valid qubit state");
        }
        
        std::string state_str = std::get<std::string>(value.value);
        
        // Handle common states
        if (state_str == "|0⟩") {
            return QuantumState({1.0, 0.0});
        } else if (state_str == "|1⟩") {
            return QuantumState({0.0, 1.0});
        } else if (state_str == "|+⟩") {
            return QuantumState({1.0/std::sqrt(2.0), 1.0/std::sqrt(2.0)});
        } else if (state_str == "|-⟩") {
            return QuantumState({1.0/std::sqrt(2.0), -1.0/std::sqrt(2.0)});
        }
        
        // More complex state parsing could be added here
        // For now, default to |0⟩ for unknown states
        return QuantumState();
    }
    
    // Measurement with random result based on probabilities
    int measure_qubit(const QuantumState& state) {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        
        double rand_val = dist(gen);
        double prob_0 = state.prob_0();
        
        return (rand_val < prob_0) ? 0 : 1;
    }
    
    // Common gates as 2x2 matrices
    namespace gates {
        // Hadamard gate
        const std::vector<std::complex<double>> H = {
            1.0/std::sqrt(2.0), 1.0/std::sqrt(2.0),
            1.0/std::sqrt(2.0), -1.0/std::sqrt(2.0)
        };
        
        // Pauli X (NOT) gate
        const std::vector<std::complex<double>> X = {
            0.0, 1.0,
            1.0, 0.0
        };
        
        // Pauli Y gate
        const std::vector<std::complex<double>> Y = {
            0.0, std::complex<double>(0.0, -1.0),
            std::complex<double>(0.0, 1.0), 0.0
        };
        
        // Pauli Z gate
        const std::vector<std::complex<double>> Z = {
            1.0, 0.0,
            0.0, -1.0
        };
        
        // S gate (sqrt(Z))
        const std::vector<std::complex<double>> S = {
            1.0, 0.0,
            0.0, std::complex<double>(0.0, 1.0)
        };
        
        // T gate (sqrt(S))
        const std::vector<std::complex<double>> T = {
            1.0, 0.0,
            0.0, std::exp(std::complex<double>(0.0, M_PI/4.0))
        };
    }
}

/**
 * @brief Quantum operations plugin for Woflang
 * 
 * This plugin provides operations for quantum computing simulation.
 */
class QuantumOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // ----- Qubit State Creation -----
        
        // |0⟩: Create a qubit in the |0⟩ state
        interp.register_op("|0⟩", [](WoflangInterpreter& interp) {
            QuantumState state({1.0, 0.0});
            interp.stack.push_back(quantum_helpers::state_to_wof(state));
            std::cout << "Created |0⟩ state\n";
        });
        
        // |1⟩: Create a qubit in the |1⟩ state
        interp.register_op("|1⟩", [](WoflangInterpreter& interp) {
            QuantumState state({0.0, 1.0});
            interp.stack.push_back(quantum_helpers::state_to_wof(state));
            std::cout << "Created |1⟩ state\n";
        });
        
        // |+⟩: Create a qubit in the |+⟩ state
        interp.register_op("|+⟩", [](WoflangInterpreter& interp) {
            QuantumState state({1.0/std::sqrt(2.0), 1.0/std::sqrt(2.0)});
            interp.stack.push_back(quantum_helpers::state_to_wof(state));
            std::cout << "Created |+⟩ state\n";
        });
        
        // |-⟩: Create a qubit in the |-⟩ state
        interp.register_op("|-⟩", [](WoflangInterpreter& interp) {
            QuantumState state({1.0/std::sqrt(2.0), -1.0/std::sqrt(2.0)});
            interp.stack.push_back(quantum_helpers::state_to_wof(state));
            std::cout << "Created |-⟩ state\n";
        });
        
        // |ψ⟩: Create a random superposition state
        interp.register_op("|ψ⟩", [](WoflangInterpreter& interp) {
            static std::mt19937 gen(std::random_device{}());
            std::uniform_real_distribution<double> dist(0.0, 1.0);
            
            double theta = dist(gen) * M_PI;
            double phi = dist(gen) * 2.0 * M_PI;
            
            std::complex<double> alpha = std::cos(theta);
            std::complex<double> beta = std::exp(std::complex<double>(0.0, phi)) * std::sin(theta);
            
            QuantumState state({alpha, beta});
            interp.stack.push_back(quantum_helpers::state_to_wof(state));
            std::cout << "Created random superposition state\n";
        });
        
        // ----- Quantum Gates -----
        
        // H: Apply Hadamard gate
        interp.register_op("H", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on H");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            try {
                QuantumState state = quantum_helpers::wof_to_state(value);
                state.apply_gate(quantum_helpers::gates::H);
                interp.stack.push_back(quantum_helpers::state_to_wof(state));
                std::cout << "Applied Hadamard gate\n";
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("H gate error: ") + e.what());
            }
        });
        
        // X: Apply Pauli X gate (NOT)
        interp.register_op("X", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on X");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            try {
                QuantumState state = quantum_helpers::wof_to_state(value);
                state.apply_gate(quantum_helpers::gates::X);
                interp.stack.push_back(quantum_helpers::state_to_wof(state));
                std::cout << "Applied Pauli X gate\n";
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("X gate error: ") + e.what());
            }
        });
        
        // Y: Apply Pauli Y gate
        interp.register_op("Y", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on Y");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            try {
                QuantumState state = quantum_helpers::wof_to_state(value);
                state.apply_gate(quantum_helpers::gates::Y);
                interp.stack.push_back(quantum_helpers::state_to_wof(state));
                std::cout << "Applied Pauli Y gate\n";
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("Y gate error: ") + e.what());
            }
        });
        
        // Z: Apply Pauli Z gate
        interp.register_op("Z", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on Z");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            try {
                QuantumState state = quantum_helpers::wof_to_state(value);
                state.apply_gate(quantum_helpers::gates::Z);
                interp.stack.push_back(quantum_helpers::state_to_wof(state));
                std::cout << "Applied Pauli Z gate\n";
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("Z gate error: ") + e.what());
            }
        });
        
        // S: Apply S gate
        interp.register_op("S", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on S");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            try {
                QuantumState state = quantum_helpers::wof_to_state(value);
                state.apply_gate(quantum_helpers::gates::S);
                interp.stack.push_back(quantum_helpers::state_to_wof(state));
                std::cout << "Applied S gate\n";
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("S gate error: ") + e.what());
            }
        });
        
        // T: Apply T gate
        interp.register_op("T", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on T");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            try {
                QuantumState state = quantum_helpers::wof_to_state(value);
                state.apply_gate(quantum_helpers::gates::T);
                interp.stack.push_back(quantum_helpers::state_to_wof(state));
                std::cout << "Applied T gate\n";
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("T gate error: ") + e.what());
            }
        });
        
        // ----- Measurement and Inspection -----
        
        // measure: Measure a qubit and collapse its state
        interp.register_op("measure", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on measure");
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            try {
                QuantumState state = quantum_helpers::wof_to_state(value);
                
                // Output probabilities
                std::cout << "Measurement probabilities:\n";
                std::cout << "  |0⟩: " << std::fixed << std::setprecision(4) << state.prob_0() * 100.0 << "%\n";
                std::cout << "  |1⟩: " << std::fixed << std::setprecision(4) << state.prob_1() * 100.0 << "%\n";
                
                // Perform measurement
                int result = quantum_helpers::measure_qubit(state);
                
                // Create collapsed state
                QuantumState collapsed = (result == 0) ? 
                    QuantumState({1.0, 0.0}) : QuantumState({0.0, 1.0});
                
                // Push result
                interp.stack.emplace_back(static_cast<int64_t>(result));
                
                // Output result
                std::cout << "Measured: |" << result << "⟩\n";
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("Measurement error: ") + e.what());
            }
        });
        
        // inspect: Show qubit state without measuring
        interp.register_op("inspect", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on inspect");
            }
            
            auto value = interp.stack.back();
            
            try {
                QuantumState state = quantum_helpers::wof_to_state(value);
                
                // Output detailed state information
                std::cout << "Qubit state: " << state.to_string() << "\n";
                std::cout << "Amplitudes:\n";
                std::cout << "  |0⟩: " << state.amplitudes[0] << " (prob: " 
                         << std::fixed << std::setprecision(4) << state.prob_0() * 100.0 << "%)\n";
                std::cout << "  |1⟩: " << state.amplitudes[1] << " (prob: " 
                         << std::fixed << std::setprecision(4) << state.prob_1() * 100.0 << "%)\n";
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("Inspection error: ") + e.what());
            }
        });
        
        // ----- Educational and Demo Operations -----
        
        // bell_pair: Create a Bell pair (entangled qubits)
        interp.register_op("bell_pair", [](WoflangInterpreter& interp) {
            std::cout << "Bell Pair (Educational Demonstration)\n";
            std::cout << "-----------------------------------\n";
            std::cout << "Step 1: Start with |0⟩|0⟩\n";
            std::cout << "Step 2: Apply H to first qubit: (|0⟩+|1⟩)/√2 |0⟩\n";
            std::cout << "Step 3: Apply CNOT: (|00⟩+|11⟩)/√2\n";
            std::cout << "Result: Entangled Bell pair\n\n";
            
            std::cout << "Note: This is a demonstration. In actual quantum\n";
            std::cout << "computing, this would create entanglement between\n";
            std::cout << "two qubits. Woflang currently simulates only single qubits.\n";
            
            // Push a symbol representing the bell pair
            WofValue bell_pair("bell_pair", WofType::Symbol);
            bell_pair.unit = "educational";
            interp.stack.push_back(bell_pair);
        });
        
        // quantum_teleportation: Demonstrate quantum teleportation protocol
        interp.register_op("quantum_teleportation", [](WoflangInterpreter& interp) {
            std::cout << "Quantum Teleportation Protocol (Educational Demonstration)\n";
            std::cout << "-------------------------------------------------------\n";
            std::cout << "Step 1: Create Bell pair between Alice and Bob\n";
            std::cout << "Step 2: Alice entangles her data qubit with her Bell pair qubit\n";
            std::cout << "Step 3: Alice measures her two qubits\n";
            std::cout << "Step 4: Alice sends classical bits to Bob\n";
            std::cout << "Step 5: Bob applies correction operations based on Alice's bits\n";
            std::cout << "Result: Bob's qubit now has the state of Alice's original data qubit\n\n";
            
            std::cout << "Note: This is a demonstration of the quantum teleportation\n";
            std::cout << "protocol which would require multiple qubits and classical\n";
            std::cout << "communication. Woflang currently simulates only single qubits.\n";
            
            // Push a symbol representing the teleportation
            WofValue teleportation("teleportation", WofType::Symbol);
            teleportation.unit = "educational";
            interp.stack.push_back(teleportation);
        });
        
        // quantum_info: Display educational information about quantum computing
        interp.register_op("quantum_info", [](WoflangInterpreter& interp) {
            std::cout << "=== Quantum Computing Information ===\n\n";
            std::cout << "Quantum computing uses quantum bits (qubits) that can exist in\n";
            std::cout << "superpositions of states, unlike classical bits that are either 0 or 1.\n\n";
            
            std::cout << "Key concepts:\n";
            std::cout << "  - Superposition: Qubits can be in multiple states simultaneously\n";
            std::cout << "  - Entanglement: Quantum correlation between separate qubits\n";
            std::cout << "  - Measurement: Collapses a qubit to a classical state\n\n";
            
            std::cout << "Common gates:\n";
            std::cout << "  - H (Hadamard): Creates superposition\n";
            std::cout << "  - X (NOT): Flips |0⟩ to |1⟩ and vice versa\n";
            std::cout << "  - Z: Phase flip, |1⟩ becomes -|1⟩\n";
            std::cout << "  - S, T: Phase gates (rotations around Z-axis)\n\n";
            
            std::cout << "Woflang provides a simple single-qubit simulator to demonstrate\n";
            std::cout << "these concepts, though real quantum computing would involve\n";
            std::cout << "multiple qubits and more complex operations.\n";
        });
    }
};

} // namespace woflang

// Plugin registration function
WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::QuantumOpsPlugin plugin;
    plugin.register_ops(interp);
}