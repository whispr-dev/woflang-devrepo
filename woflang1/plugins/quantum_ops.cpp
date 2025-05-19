/**
 * @file woflang.hpp
 * @brief Main header file for Woflang
 * 
 * This file provides the core types and classes for the Woflang stack-based
 * programming language.
 */

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdexcept>
#include <optional>
#include <random>
#include <chrono>
#include <complex>

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
#   define WOFLANG_PLATFORM_WINDOWS
#   include <windows.h>
#else
#   define WOFLANG_PLATFORM_UNIX
#   include <dlfcn.h>
#endif

namespace woflang {

/**
 * @brief Value types supported by Woflang
 */
enum class WofType {
    Integer,    ///< 64-bit signed integer
    Double,     ///< Double-precision floating point
    String,     ///< String (quoted text)
    Symbol      ///< Symbol (unquoted identifier)
};

/**
 * @brief Main value class for Woflang
 * 
 * This class represents values on the stack and in the language.
 */
class WofValue {
public:
    /// The type of this value
    WofType type;
    
    /// The actual value stored as a variant
    std::variant<int64_t, double, std::string> value;
    
    /// Optional unit for the value (e.g., "m" for meters)
    std::optional<std::string> unit;
    
    /// Constructor for integer values
    explicit WofValue(int64_t i) : type(WofType::Integer), value(i) {}
    
    /// Constructor for double values
    explicit WofValue(double d) : type(WofType::Double), value(d) {}
    
    /// Constructor for string/symbol values
    explicit WofValue(const std::string& s, WofType t = WofType::String) 
        : type(t), value(s) {}
    
    /// Default constructor (used internally)
    WofValue() : type(WofType::Integer), value(0LL) {}
    
    /// Copy constructor
    WofValue(const WofValue&) = default;
    
    /// Move constructor
    WofValue(WofValue&&) = default;
    
    /// Copy assignment
    WofValue& operator=(const WofValue&) = default;
    
    /// Move assignment
    WofValue& operator=(WofValue&&) = default;
    
    // Missing beginning of code 3.cpp (equality operator implementation)
    bool operator==(const WofValue& other) const {
        if (type != other.type || unit != other.unit) {
            return false;
        }
        
        switch (type) {
            case WofType::Integer:
                return std::get<int64_t>(value) == std::get<int64_t>(other.value);
            case WofType::Double:
                return std::get<double>(value) == std::get<double>(other.value);
            case WofType::String:
            case WofType::Symbol:
                return std::get<std::string>(value) == std::get<std::string>(other.value);
            default:
                return false;
        }
    }
};

struct QubitState {
    std::vector<std::complex<double>> amplitudes;  // For |0⟩ and |1⟩
    
    // Helper to check if the state is normalized
    bool is_normalized() const {
        double sum = 0.0;
        for (const auto& amp : amplitudes) {
            sum += std::norm(amp);  // |amplitude|^2
        }
        return std::abs(sum - 1.0) < 1e-10;
    }
};

class QuantumOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // Set up random number generator for measurements
        static std::mt19937 gen(std::random_device{}());
        static std::uniform_real_distribution<double> dist(0.0, 1.0);
        
        // Create a qubit in |0⟩ state
        interp.register_op("qubit0", [](WoflangInterpreter& interp) {
            QubitState state = {{1.0, 0.0}};  // |0⟩
            interp.stack.push_back(qubit_to_wof(state));
            std::cout << "Created |0⟩ qubit\n";
        });
        
        // Create a qubit in |1⟩ state
        interp.register_op("qubit1", [](WoflangInterpreter& interp) {
            QubitState state = {{0.0, 1.0}};  // |1⟩
            interp.stack.push_back(qubit_to_wof(state));
            std::cout << "Created |1⟩ qubit\n";
        });
        
        // Create a qubit in |+⟩ state
        interp.register_op("qubit+", [](WoflangInterpreter& interp) {
            // |+⟩ = (|0⟩ + |1⟩)/√2
            double factor = 1.0 / std::sqrt(2.0);
            QubitState state = {{factor, factor}};
            interp.stack.push_back(qubit_to_wof(state));
            std::cout << "Created |+⟩ qubit\n";
        });
        
        // Create a qubit in |-⟩ state
        interp.register_op("qubit-", [](WoflangInterpreter& interp) {
            // |-⟩ = (|0⟩ - |1⟩)/√2
            double factor = 1.0 / std::sqrt(2.0);
            QubitState state = {{factor, -factor}};
            interp.stack.push_back(qubit_to_wof(state));
            std::cout << "Created |-⟩ qubit\n";
        });
        
        // H: Apply the Hadamard gate to the qubit on top of the stack
        interp.register_op("H", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "H: Stack empty\n";
                return;
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            // Check if it's a qubit
            if (!value.unit || *value.unit != "qubit") {
                std::cout << "H: Top of stack is not a qubit\n";
                interp.stack.push_back(value);
                return;
            }
            
            // Apply the Hadamard gate
            if (value.type == WofType::Symbol) {
                std::string state_str = std::get<std::string>(value.value);
                
                // Simple approach: check for specific states
                if (state_str.find("|0⟩") != std::string::npos && state_str.find("|1⟩") == std::string::npos) {
                    // |0⟩ -> |+⟩
                    QubitState state = {{1.0/std::sqrt(2.0), 1.0/std::sqrt(2.0)}};
                    interp.stack.push_back(qubit_to_wof(state));
                    std::cout << "H|0⟩ = |+⟩\n";
                } else if (state_str.find("|1⟩") != std::string::npos && state_str.find("|0⟩") == std::string::npos) {
                    // |1⟩ -> |-⟩
                    QubitState state = {{1.0/std::sqrt(2.0), -1.0/std::sqrt(2.0)}};
                    interp.stack.push_back(qubit_to_wof(state));
                    std::cout << "H|1⟩ = |-⟩\n";
                } else if (state_str.find("|+⟩") != std::string::npos) {
                    // |+⟩ -> |0⟩
                    QubitState state = {{1.0, 0.0}};
                    interp.stack.push_back(qubit_to_wof(state));
                    std::cout << "H|+⟩ = |0⟩\n";
                } else if (state_str.find("|-⟩") != std::string::npos) {
                    // |-⟩ -> |1⟩
                    QubitState state = {{0.0, 1.0}};
                    interp.stack.push_back(qubit_to_wof(state));
                    std::cout << "H|-⟩ = |1⟩\n";
                } else {
                    // For other states, just note the operation
                    std::cout << "H: Applied Hadamard gate (simplified)\n";
                    std::string result = "H(";
                    result += state_str;
                    result += ")";
                    value.value = result;
                    interp.stack.push_back(value);
                }
            } else {
                // Not a qubit state we can handle
                std::cout << "H: Can't apply Hadamard to this value\n";
                interp.stack.push_back(value);
            }
        });
        
        // X: Apply the Pauli X (bit flip) gate to the qubit on top of the stack
        interp.register_op("X", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "X: Stack empty\n";
                return;
            }
            
            auto value = interp.stack.back(); interp.stack.pop_back();
    // Then the provided mid_mystery_guest.cpp fragment continues with abs, neg, min, max, etc.
    }
    // abs: Absolute value
    interp.register_op("abs", [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            throw std::runtime_error("Stack underflow on abs");
        }
        
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        if (a.type == WofType::Integer) {
            // Integer absolute value
            interp.stack.emplace_back(std::abs(std::get<int64_t>(a.value)));
        } else if (a.type == WofType::Double) {
            // Double absolute value
            interp.stack.emplace_back(std::abs(std::get<double>(a.value)));
        } else {
            throw std::runtime_error("Type error: abs requires a numeric value");
        }
    });
    
    // neg: Negate a value
    interp.register_op("neg", [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            throw std::runtime_error("Stack underflow on neg");
        }
        
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        if (a.type == WofType::Integer) {
            // Integer negation
            interp.stack.emplace_back(-std::get<int64_t>(a.value));
        } else if (a.type == WofType::Double) {
            // Double negation
            interp.stack.emplace_back(-std::get<double>(a.value));
        } else {
            throw std::runtime_error("Type error: neg requires a numeric value");
        }
    });
    
    // min: Minimum of two values
    interp.register_op("min", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            throw std::runtime_error("Stack underflow on min");
        }
        
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        if (a.type == WofType::Integer && b.type == WofType::Integer) {
            // Integer minimum
            interp.stack.emplace_back(std::min(std::get<int64_t>(a.value), std::get<int64_t>(b.value)));
        } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                   (b.type == WofType::Integer || b.type == WofType::Double)) {
            // Mixed or double minimum
            double val_a = a.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
            double val_b = b.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
            
            interp.stack.emplace_back(std::min(val_a, val_b));
        } else {
            throw std::runtime_error("Type error: min requires numeric values");
        }
    });
    
    // max: Maximum of two values
    interp.register_op("max", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            throw std::runtime_error("Stack underflow on max");
        }
        
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        if (a.type == WofType::Integer && b.type == WofType::Integer) {
            // Integer maximum
            interp.stack.emplace_back(std::max(std::get<int64_t>(a.value), std::get<int64_t>(b.value)));
        } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                   (b.type == WofType::Integer || b.type == WofType::Double)) {
            // Mixed or double maximum
            double val_a = a.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
            double val_b = b.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
            
            interp.stack.emplace_back(std::max(val_a, val_b));
        } else {
            throw std::runtime_error("Type error: max requires numeric values");
        }
    });
    
    // ----- Comparison Operations -----
    
    // =: Check if two values are equal
    interp.register_op("=", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            throw std::runtime_error("Stack underflow on =");
        }
        
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        // Compare based on types
        bool equal = false;
        
        if (a.type == b.type) {
            // Same type, direct comparison
            switch (a.type) {
                case WofType::Integer:
                    equal = std::get<int64_t>(a.value) == std::get<int64_t>(b.value);
                    break;
                case WofType::Double:
                    equal = std::get<double>(a.value) == std::get<double>(b.value);
                    break;
                case WofType::String:
                case WofType::Symbol:
                    equal = std::get<std::string>(a.value) == std::get<std::string>(b.value);
                    break;
            }
        } else if ((a.type == WofType::Integer && b.type == WofType::Double) ||
                   (a.type == WofType::Double && b.type == WofType::Integer)) {
            // Mixed numeric comparison
            double val_a = a.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
            double val_b = b.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
            
            equal = val_a == val_b;
        }
        
        // Push result as integer (1 for true, 0 for false)
        interp.stack.emplace_back(equal ? 1LL : 0LL);
    });
    
    // <>: Check if two values are not equal
    interp.register_op("<>", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            throw std::runtime_error("Stack underflow on <>");
        }
        
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        // Compare based on types
        bool not_equal = true;
        
        if (a.type == b.type) {
            // Same type, direct comparison
            switch (a.type) {
                case WofType::Integer:
                    not_equal = std::get<int64_t>(a.value) != std::get<int64_t>(b.value);
                    break;
                case WofType::Double:
                    not_equal = std::get<double>(a.value) != std::get<double>(b.value);
                    break;
                case WofType::String:
                case WofType::Symbol:
                    not_equal = std::get<std::string>(a.value) != std::get<std::string>(b.value);
                    break;
            }
        } else if ((a.type == WofType::Integer && b.type == WofType::Double) ||
                   (a.type == WofType::Double && b.type == WofType::Integer)) {
            // Mixed numeric comparison
            double val_a = a.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
            double val_b = b.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
            
            not_equal = val_a != val_b;
        }
        
        // Push result as integer (1 for true, 0 for false)
        interp.stack.emplace_back(not_equal ? 1LL : 0LL);
    });
    
    // <: Check if a is less than b
    interp.register_op("<", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            throw std::runtime_error("Stack underflow on <");
        }
        
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        // Compare based on types
        bool less_than = false;
        
        if (a.type == WofType::Integer && b.type == WofType::Integer) {
            // Integer comparison
            less_than = std::get<int64_t>(a.value) < std::get<int64_t>(b.value);
        } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                   (b.type == WofType::Integer || b.type == WofType::Double)) {
            // Mixed or double comparison
            double val_a = a.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
            double val_b = b.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
            
            less_than = val_a < val_b;
        } else if ((a.type == WofType::String || a.type == WofType::Symbol) && 
                   (b.type == WofType::String || b.type == WofType::Symbol)) {
            // String comparison
            less_than = std::get<std::string>(a.value) < std::get<std::string>(b.value);
        } else {
            throw std::runtime_error("Type error: < requires comparable types");
        }
        
        // Push result as integer (1 for true, 0 for false)
        interp.stack.emplace_back(less_than ? 1LL : 0LL);
    });
    
    // >: Check if a is greater than b
    interp.register_op(">", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            throw std::runtime_error("Stack underflow on >");
        }
        
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        // Compare based on types
        bool greater_than = false;
        
        if (a.type == WofType::Integer && b.type == WofType::Integer) {
            // Integer comparison
            greater_than = std::get<int64_t>(a.value) > std::get<int64_t>(b.value);
        } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                   (b.type == WofType::Integer || b.type == WofType::Double)) {
            // Mixed or double comparison
            double val_a = a.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
            double val_b = b.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
            
            greater_than = val_a > val_b;
        } else if ((a.type == WofType::String || a.type == WofType::Symbol) && 
                   (b.type == WofType::String || b.type == WofType::Symbol)) {
            // String comparison
            greater_than = std::get<std::string>(a.value) > std::get<std::string>(b.value);
        } else {
            throw std::runtime_error("Type error: > requires comparable types");
        }
        
        // Push result as integer (1 for true, 0 for false)
        interp.stack.emplace_back(greater_than ? 1LL : 0LL);
    });
    
    // <=: Check if a is less than or equal to b
    interp.register_op("<=", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            throw std::runtime_error("Stack underflow on <=");
        }
        
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        // Compare based on types
        bool less_or_equal = false;
        
        if (a.type == WofType::Integer && b.type == WofType::Integer) {
            // Integer comparison
            less_or_equal = std::get<int64_t>(a.value) <= std::get<int64_t>(b.value);
        } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                   (b.type == WofType::Integer || b.type == WofType::Double)) {
            // Mixed or double comparison
            double val_a = a.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
            double val_b = b.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
            
            less_or_equal = val_a <= val_b;
        } else if ((a.type == WofType::String || a.type == WofType::Symbol) && 
                   (b.type == WofType::String || b.type == WofType::Symbol)) {
            // String comparison
            less_or_equal = std::get<std::string>(a.value) <= std::get<std::string>(b.value);
        } else {
            throw std::runtime_error("Type error: <= requires comparable types");
        }
        
        // Push result as integer (1 for true, 0 for false)
        interp.stack.emplace_back(less_or_equal ? 1LL : 0LL);
    });
    
    // >=: Check if a is greater than or equal to b
    interp.register_op(">=", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            throw std::runtime_error("Stack underflow on >=");
        }
        
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        // Compare based on types
        bool greater_or_equal = false;
        
        if (a.type == WofType::Integer && b.type == WofType::Integer) {
            // Integer comparison
            greater_or_equal = std::get<int64_t>(a.value) >= std::get<int64_t>(b.value);
        } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                   (b.type == WofType::Integer || b.type == WofType::Double)) {
            // Mixed or double comparison
            double val_a = a.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
            double val_b = b.type == WofType::Integer ? 
                static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
            
            greater_or_equal = val_a >= val_b;
        } else if ((a.type == WofType::String || a.type == WofType::Symbol) && 
                   (b.type == WofType::String || b.type == WofType::Symbol)) {
            // String comparison
            greater_or_equal = std::get<std::string>(a.value) >= std::get<std::string>(b.value);
        } else {
            throw std::runtime_error("Type error: >= requires comparable types");
        }
        
        // Push result as integer (1 for true, 0 for false)
        interp.stack.emplace_back(greater_or_equal ? 1LL : 0LL);
    });
    
    // ----- Logic Operations -----
    
    // and: Logical AND
    interp.register_op("and", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            throw std::runtime_error("Stack underflow on and");
        }
        
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        // Convert to boolean values
        bool bool_a = false;
        bool bool_b = false;
        
        if (a.type == WofType::Integer) {
            bool_a = std::get<int64_t>(a.value) != 0;
        } else if (a.type == WofType::Double) {
            bool_a = std::get<double>(a.value) != 0.0;
        } else {
            throw std::runtime_error("Type error: and requires numeric values");
        }
        
        if (b.type == WofType::Integer) {
            bool_b = std::get<int64_t>(b.value) != 0;
        } else if (b.type == WofType::Double) {
            bool_b = std::get<double>(b.value) != 0.0;
        } else {
            throw std::runtime_error("Type error: and requires numeric values");
        }
        
        // Push result as integer (1 for true, 0 for false)
        interp.stack.emplace_back(bool_a && bool_b ? 1LL : 0LL);
    });
    
    // or: Logical OR
    interp.register_op("or", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            throw std::runtime_error("Stack underflow on or");
        }
        
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        // Convert to boolean values
        bool bool_a = false;
        bool bool_b = false;
        
        if (a.type == WofType::Integer) {
            bool_a = std::get<int64_t>(a.value) != 0;
        } else if (a.type == WofType::Double) {
            bool_a = std::get<double>(a.value) != 0.0;
        } else {
            throw std::runtime_error("Type error: or requires numeric values");
        }
        
        if (b.type == WofType::Integer) {
            bool_b = std::get<int64_t>(b.value) != 0;
        } else if (b.type == WofType::Double) {
            bool_b = std::get<double>(b.value) != 0.0;
        } else {
            throw std::runtime_error("Type error: or requires numeric values");
        }
        
        // Push result as integer (1 for true, 0 for false)
        interp.stack.emplace_back(bool_a || bool_b ? 1LL : 0LL);
    });
    
    // not: Logical NOT
    interp.register_op("not", [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            throw std::runtime_error("Stack underflow on not");
        }
        
        auto a = interp.stack.back(); interp.stack.pop_back();
        
        // Convert to boolean value
        bool bool_a = false;
        
        if (a.type == WofType::Integer) {
            bool_a = std::get<int64_t>(a.value) != 0;
        } else if (a.type == WofType::Double) {
            bool_a = std::get<double>(a.value) != 0.0;
        } else {
            throw std::runtime_error("Type error: not requires a numeric value");
        }
        
        // Push result as integer (1 for true, 0 for false)
        interp.stack.emplace_back(!bool_a ? 1LL : 0LL);
    });
    
    // ----- Math Constants -----
    
    // pi: Push π onto the stack
    interp.register_op("pi", [](WoflangInterpreter& interp) {
        interp.stack.emplace_back(3.14159265358979323846);
    });
    
    // e: Push e onto the stack
    interp.register_op("e", [](WoflangInterpreter& interp) {
        interp.stack.emplace_back(2.71828182845904523536);
    });
    
    // ----- I/O Operations -----
    
    // print: Print the top value on the stack
    interp.register_op("print", [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            throw std::runtime_error("Stack underflow on print");
        }
        
        const auto& value = interp.stack.back();
        std::cout << value.to_string() << std::endl;
    });
    
    // .: Print the top value and pop it
    interp.register_op(".", [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            throw std::runtime_error("Stack underflow on .");
        }
        
        const auto& value = interp.stack.back();
        std::cout << value.to_string() << " ";
        interp.stack.pop_back();
    });
    
    // .s: Display the entire stack
    interp.register_op(".s", [](WoflangInterpreter& interp) {
        interp.print_stack();
    });
    
    // clear: Clear the stack
    interp.register_op("clear", [](WoflangInterpreter& interp) {
        interp.clear_stack();
    });
    
    // ----- Sacred/Special Operations -----
    
    // Random number generator for sacred ops
    static std::mt19937 rng(
        static_cast<unsigned int>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count()
        )
    );
    
    // entropy: Calculate and display stack entropy
    interp.register_op("entropy", [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            std::cout << "∴  Entropy: 0.0 (empty stack)\n";
            return;
        }
        
        std::unordered_map<std::string, int> freq;
        for (const auto& v : interp.stack) {
            // Convert value to string for frequency count
            std::string s = v.to_string();
            freq[s]++;
        }
        
        // Calculate Shannon entropy: -sum(p_i * log2(p_i))
        double entropy = 0.0;
        double n = static_cast<double>(interp.stack.size());
        
        for (const auto& [_, count] : freq) {
            double p = static_cast<double>(count) / n;
            entropy -= p * std::log2(p);
        }
        
        std::cout << "∴  Entropy: " << entropy << "\n";
    });
    
    // prophecy: Output a cryptic "prophecy" about the stack
    interp.register_op("prophecy", [&rng](WoflangInterpreter&) {
        static const std::vector<std::string> prophecies = {
            "In the glyph's shadow, your stack's fate is sealed.",
            "Beware: The next push may tip the void.",
            "The stack will echo your intent, not your command.",
            "A silent glyph is the most powerful of all.",
            "The void grows with each lost symbol.",
            "A stack unbalanced is a prophecy unfulfilled.",
            "Beware the glyph echoing twice.",
            "All symbols return to void at the end.",
            "He who divides by zero will see the face of the stack void.",
            "All prophecy is self-fulfilling in woflang."
        };
        
        std::uniform_int_distribution<size_t> dist(0, prophecies.size() - 1);
        std::cout << "[Prophecy] " << prophecies[dist(rng)] << std::endl;
    });
    
    // egg: Easter egg operation
    interp.register_op("egg", [](WoflangInterpreter&) {
        std::cout << "🥚  You have discovered the Joy Egg! May your stack never underflow!" << std::endl;
    });
    
    // stack_slayer: Clear the stack with a dramatic message
    interp.register_op("stack_slayer", [](WoflangInterpreter& interp) {
        std::cout << "☠️  The void has claimed your stack! (All items erased)" << std::endl;
        interp.clear_stack();
    });
    
    // sigil_map: Display all sacred sigils
    interp.register_op("sigil_map", [](WoflangInterpreter&) {
        std::cout << "Sacred Sigils:\n"
                 << "prophecy (🔮): Cryptic stack fate message\n"
                 << "stack_slayer (☠️): Destroys the stack (forbidden)\n"
                 << "egg (🥚): Joy Easter Egg\n"
                 << "glyph_prophecy (🜄): Secret, full-moon only\n"
                 << "omega (Ω): Session ending\n"
                 << "sigil_map (🗺️): This map\n"
                 << "entropy (∴): Stack entropy measure\n"
                 << "void_division (⦰): Divides by the void (forbidden)\n"
                 << "duality (☯️): Inverts the next op (metaphysical)\n"
                 << "over_unity (⚡): Energy exceeds input (physics easter egg)\n";
    });
    
    // omega: End the session
    interp.register_op("omega", [](WoflangInterpreter&) {
        std::cout << "Ω  All cycles end. The interpreter closes. Until next session, fren!" << std::endl;
        std::exit(0);
    });
    
    // void_division: Divide by zero with dramatic effect
    interp.register_op("void_division", [](WoflangInterpreter& interp) {
        if (interp.stack.empty() || 
            ((interp.stack.back().type == WofType::Integer && std::get<int64_t>(interp.stack.back().value) == 0) ||
             (interp.stack.back().type == WofType::Double && std::get<double>(interp.stack.back().value) == 0.0))) {
            std::cout << "⦰  The void divides all. Stack erased. 'Beware division by zero.'\n";
            interp.clear_stack();
        } else {
            std::cout << "⦰  Only the zero can invoke the void. Push 0 and try again.\n";
        }
    });
    
    // duality: Playful op that claims to invert the next operation
    interp.register_op("duality", [](WoflangInterpreter&) {
        std::cout << "☯️  Duality: The next op is inverted (metaphysical only).\n";
    });
    
    // over_unity: Physics easter egg
    interp.register_op("over_unity", [](WoflangInterpreter&) {
        std::cout << "⚡  Over Unity! Energy out exceeds in. Next op will be amplified... (metaphysical)\n";
    });
    
    // glyph_prophecy: Secret operation only available during the full moon
    interp.register_op("glyph_prophecy", [](WoflangInterpreter&) {
        // A simple check for the full moon (this is just a demo - in reality you might
        // use a lunar phase calculation based on the current date)
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm* tm = std::localtime(&time);
        
        // For demo purposes, let's say it's a "full moon" on days divisible by 15
        bool is_full_moon = (tm->tm_mday % 15 == 0);
        
        if (is_full_moon) {
            std::cout << "🜄  The glyph prophecy reveals: 'All symbols return to void at the end.'" << std::endl;
        } else {
            std::cout << "The glyph prophecy can only be revealed at the full moon!" << std::endl;
        }
    });
}

} // namespace woflang