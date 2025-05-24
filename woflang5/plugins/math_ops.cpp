#include "../../src/core/woflang.hpp"
#include <cmath>
#include <iostream>

namespace woflang {

/**
 * @brief Math operations plugin for Woflang
 * 
 * This plugin provides basic mathematical operations beyond
 * the core arithmetic operations.
 */
class MathOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // ----- Basic Stack Operations -----
        
        // dup: Duplicate the top stack value
        interp.register_op("dup", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on dup");
            }
            
            interp.stack.push_back(interp.stack.back());
        });
        
        // drop: Drop the top stack value
        interp.register_op("drop", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on drop");
            }
            
            interp.stack.pop_back();
        });
        
        // swap: Swap the top two stack values
        interp.register_op("swap", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on swap");
            }
            
            std::swap(interp.stack[interp.stack.size() - 1], interp.stack[interp.stack.size() - 2]);
        });
        
        // over: Duplicate the second stack value to the top
        interp.register_op("over", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on over");
            }
            
            interp.stack.push_back(interp.stack[interp.stack.size() - 2]);
        });
        
        // rot: Rotate the top three stack values
        interp.register_op("rot", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 3) {
                throw std::runtime_error("Stack underflow on rot");
            }
            
            auto a = interp.stack[interp.stack.size() - 3];
            auto b = interp.stack[interp.stack.size() - 2];
            auto c = interp.stack[interp.stack.size() - 1];
            
            interp.stack[interp.stack.size() - 3] = b;
            interp.stack[interp.stack.size() - 2] = c;
            interp.stack[interp.stack.size() - 1] = a;
        });
        
        // ----- Arithmetic Operations -----
        
        // +: Add two values
        interp.register_op("+", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on +");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer && b.type == WofType::Integer) {
                // Integer addition
                interp.stack.emplace_back(std::get<int64_t>(a.value) + std::get<int64_t>(b.value));
            } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                       (b.type == WofType::Integer || b.type == WofType::Double)) {
                // Mixed or double addition
                double val_a = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                double val_b = b.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
                
                interp.stack.emplace_back(val_a + val_b);
            } else if ((a.type == WofType::String || a.type == WofType::Symbol) && 
                       (b.type == WofType::String || b.type == WofType::Symbol)) {
                // String concatenation
                std::string val_a = std::get<std::string>(a.value);
                std::string val_b = std::get<std::string>(b.value);
                
                if (a.type == WofType::String) {
                    // Remove the closing quote
                    val_a = val_a.substr(0, val_a.size() - 1);
                }
                
                if (b.type == WofType::String) {
                    // Remove the opening quote
                    val_b = val_b.substr(1);
                }
                
                interp.stack.emplace_back(val_a + val_b, a.type);
            } else {
                throw std::runtime_error("Type error: + requires matching numeric or string types");
            }
        });
        
        // -: Subtract two values
        interp.register_op("-", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on -");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer && b.type == WofType::Integer) {
                // Integer subtraction
                interp.stack.emplace_back(std::get<int64_t>(a.value) - std::get<int64_t>(b.value));
            } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                       (b.type == WofType::Integer || b.type == WofType::Double)) {
                // Mixed or double subtraction
                double val_a = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                double val_b = b.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
                
                interp.stack.emplace_back(val_a - val_b);
            } else {
                throw std::runtime_error("Type error: - requires numeric values");
            }
        });
        
        // *: Multiply two values
        interp.register_op("*", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on *");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer && b.type == WofType::Integer) {
                // Integer multiplication
                interp.stack.emplace_back(std::get<int64_t>(a.value) * std::get<int64_t>(b.value));
            } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                       (b.type == WofType::Integer || b.type == WofType::Double)) {
                // Mixed or double multiplication
                double val_a = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                double val_b = b.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
                
                interp.stack.emplace_back(val_a * val_b);
            } else {
                throw std::runtime_error("Type error: * requires numeric values");
            }
        });
        
        // /: Divide two values
        interp.register_op("/", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on /");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Check for division by zero
            if ((b.type == WofType::Integer && std::get<int64_t>(b.value) == 0) ||
                (b.type == WofType::Double && std::get<double>(b.value) == 0.0)) {
                throw std::runtime_error("Division by zero");
            }
            
            if (a.type == WofType::Integer && b.type == WofType::Integer) {
                // Integer division (floating point result)
                interp.stack.emplace_back(static_cast<double>(std::get<int64_t>(a.value)) / 
                                         static_cast<double>(std::get<int64_t>(b.value)));
            } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                       (b.type == WofType::Integer || b.type == WofType::Double)) {
                // Mixed or double division
                double val_a = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                double val_b = b.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
                
                interp.stack.emplace_back(val_a / val_b);
            } else {
                throw std::runtime_error("Type error: / requires numeric values");
            }
        });
        
        // mod: Modulo operation
        interp.register_op("mod", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on mod");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Check for modulo by zero
            if ((b.type == WofType::Integer && std::get<int64_t>(b.value) == 0) ||
                (b.type == WofType::Double && std::get<double>(b.value) == 0.0)) {
                throw std::runtime_error("Modulo by zero");
            }
            
            if (a.type == WofType::Integer && b.type == WofType::Integer) {
                // Integer modulo
                interp.stack.emplace_back(std::get<int64_t>(a.value) % std::get<int64_t>(b.value));
            } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                       (b.type == WofType::Integer || b.type == WofType::Double)) {
                // Mixed or double modulo (using fmod)
                double val_a = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                double val_b = b.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
                
                interp.stack.emplace_back(std::fmod(val_a, val_b));
            } else {
                throw std::runtime_error("Type error: mod requires numeric values");
            }
        });
        
        // idiv: Integer division
        interp.register_op("idiv", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on idiv");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Check for division by zero
            if ((b.type == WofType::Integer && std::get<int64_t>(b.value) == 0) ||
                (b.type == WofType::Double && std::get<double>(b.value) == 0.0)) {
                throw std::runtime_error("Division by zero");
            }
            
            if (a.type == WofType::Integer && b.type == WofType::Integer) {
                // Integer division (integer result)
                interp.stack.emplace_back(std::get<int64_t>(a.value) / std::get<int64_t>(b.value));
            } else {
                throw std::runtime_error("Type error: idiv requires integer values");
            }
        });
        
        // pow: Power operation
        interp.register_op("pow", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on pow");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                (b.type == WofType::Integer || b.type == WofType::Double)) {
                // Convert to doubles for pow
                double val_a = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                double val_b = b.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
                
                // Calculate power
                double result = std::pow(val_a, val_b);
                
                // Check if the result can be represented as an integer
                if (b.type == WofType::Integer && std::get<int64_t>(b.value) >= 0 &&
                    result == std::floor(result) && 
                    result <= static_cast<double>(std::numeric_limits<int64_t>::max()) &&
                    result >= static_cast<double>(std::numeric_limits<int64_t>::min())) {
                    // Integer power with integer result
                    interp.stack.emplace_back(static_cast<int64_t>(result));
                } else {
                    // Double result
                    interp.stack.emplace_back(result);
                }
            } else {
                throw std::runtime_error("Type error: pow requires numeric values");
            }
        });
        
        // sqrt: Square root
        interp.register_op("sqrt", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on sqrt");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer || a.type == WofType::Double) {
                // Convert to double for sqrt
                double val = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                
                // Check for negative values
                if (val < 0.0) {
                    throw std::runtime_error("Cannot take square root of negative value");
                }
                
                // Calculate square root
                double result = std::sqrt(val);
                
                // Push result
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: sqrt requires a numeric value");
            }
        });
        
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
        
        // ----- Trigonometric Operations -----
        
        // sin: Sine of angle in radians
        interp.register_op("sin", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on sin");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer || a.type == WofType::Double) {
                // Convert to double for sin
                double val = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                
                // Calculate sine
                double result = std::sin(val);
                
                // Push result
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: sin requires a numeric value");
            }
        });
        
        // cos: Cosine of angle in radians
        interp.register_op("cos", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on cos");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer || a.type == WofType::Double) {
                // Convert to double for cos
                double val = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                
                // Calculate cosine
                double result = std::cos(val);
                
                // Push result
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: cos requires a numeric value");
            }
        });
        
        // tan: Tangent of angle in radians
        interp.register_op("tan", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on tan");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer || a.type == WofType::Double) {
                // Convert to double for tan
                double val = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                
                // Calculate tangent
                double result = std::tan(val);
                
                // Push result
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: tan requires a numeric value");
            }
        });
        
        // asin: Arc sine in radians
        interp.register_op("asin", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on asin");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer || a.type == WofType::Double) {
                // Convert to double for asin
                double val = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                
                // Check domain [-1, 1]
                if (val < -1.0 || val > 1.0) {
                    throw std::runtime_error("Domain error: asin argument must be in range [-1, 1]");
                }
                
                // Calculate arc sine
                double result = std::asin(val);
                
                // Push result
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: asin requires a numeric value");
            }
        });
        
        // acos: Arc cosine in radians
        interp.register_op("acos", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on acos");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer || a.type == WofType::Double) {
                // Convert to double for acos
                double val = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                
                // Check domain [-1, 1]
                if (val < -1.0 || val > 1.0) {
                    throw std::runtime_error("Domain error: acos argument must be in range [-1, 1]");
                }
                
                // Calculate arc cosine
                double result = std::acos(val);
                
                // Push result
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: acos requires a numeric value");
            }
        });
        
        // atan: Arc tangent in radians
        interp.register_op("atan", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on atan");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer || a.type == WofType::Double) {
                // Convert to double for atan
                double val = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                
                // Calculate arc tangent
                double result = std::atan(val);
                
                // Push result
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: atan requires a numeric value");
            }
        });
        
        // atan2: Arc tangent of y/x in radians
        interp.register_op("atan2", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on atan2");
            }
            
            auto x = interp.stack.back(); interp.stack.pop_back();
            auto y = interp.stack.back(); interp.stack.pop_back();
            
            if ((y.type == WofType::Integer || y.type == WofType::Double) && 
                (x.type == WofType::Integer || x.type == WofType::Double)) {
                // Convert to doubles for atan2
                double val_y = y.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(y.value)) : std::get<double>(y.value);
                double val_x = x.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(x.value)) : std::get<double>(x.value);
                
                // Calculate arc tangent of y/x
                double result = std::atan2(val_y, val_x);
                
                // Push result
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: atan2 requires numeric values");
            }
        });
        
        // ----- Logarithmic Operations -----
        
        // ln: Natural logarithm
        interp.register_op("ln", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on ln");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer || a.type == WofType::Double) {
                // Convert to double for ln
                double val = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                
                // Check domain (x > 0)
                if (val <= 0.0) {
                    throw std::runtime_error("Domain error: ln argument must be positive");
                }
                
                // Calculate natural logarithm
                double result = std::log(val);
                
                // Push result
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: ln requires a numeric value");
            }
        });
        
        // log10: Base-10 logarithm
        interp.register_op("log10", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on log10");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer || a.type == WofType::Double) {
                // Convert to double for log10
                double val = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                
                // Check domain (x > 0)
                if (val <= 0.0) {
                    throw std::runtime_error("Domain error: log10 argument must be positive");
                }
                
                // Calculate base-10 logarithm
                double result = std::log10(val);
                
                // Push result
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: log10 requires a numeric value");
            }
        });
        
        // log: Logarithm with arbitrary base
        interp.register_op("log", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on log");
            }
            
            auto base = interp.stack.back(); interp.stack.pop_back();
            auto x = interp.stack.back(); interp.stack.pop_back();
            
            if ((x.type == WofType::Integer || x.type == WofType::Double) && 
                (base.type == WofType::Integer || base.type == WofType::Double)) {
                // Convert to doubles for log
                double val_x = x.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(x.value)) : std::get<double>(x.value);
                double val_base = base.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(base.value)) : std::get<double>(base.value);
                
                // Check domain (x > 0, base > 0, base != 1)
                if (val_x <= 0.0) {
                    throw std::runtime_error("Domain error: log argument must be positive");
                }
                if (val_base <= 0.0) {
                    throw std::runtime_error("Domain error: log base must be positive");
                }
                if (val_base == 1.0) {
                    throw std::runtime_error("Domain error: log base cannot be 1");
                }
                
                // Calculate logarithm with arbitrary base: log_b(x) = ln(x) / ln(b)
                double result = std::log(val_x) / std::log(val_base);
                
                // Push result
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: log requires numeric values");
            }
        });
        
        // exp: Exponential function (e^x)
        interp.register_op("exp", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on exp");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer || a.type == WofType::Double) {
                // Convert to double for exp
                double val = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                
                // Calculate exponential function
                double result = std::exp(val);
                
                // Push result
                interp.stack.emplace_back(result);
            } else {
                throw std::runtime_error("Type error: exp requires a numeric value");
            }
        });
        
        // ----- Additional Math Operations -----
        
        // floor: Round down to nearest integer
        interp.register_op("floor", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on floor");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer) {
                // Integer is already floored
                interp.stack.push_back(a);
            } else if (a.type == WofType::Double) {
                // Floor the double
                double val = std::get<double>(a.value);
                double result = std::floor(val);
                
                // If the result is representable as an integer, convert it
                if (result <= static_cast<double>(std::numeric_limits<int64_t>::max()) &&
                    result >= static_cast<double>(std::numeric_limits<int64_t>::min())) {
                    interp.stack.emplace_back(static_cast<int64_t>(result));
                } else {
                    interp.stack.emplace_back(result);
                }
            } else {
                throw std::runtime_error("Type error: floor requires a numeric value");
            }
        });
        
        // ceil: Round up to nearest integer
        interp.register_op("ceil", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on ceil");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer) {
                // Integer is already ceiled
                interp.stack.push_back(a);
            } else if (a.type == WofType::Double) {
                // Ceil the double
                double val = std::get<double>(a.value);
                double result = std::ceil(val);
                
                // If the result is representable as an integer, convert it
                if (result <= static_cast<double>(std::numeric_limits<int64_t>::max()) &&
                    result >= static_cast<double>(std::numeric_limits<int64_t>::min())) {
                    interp.stack.emplace_back(static_cast<int64_t>(result));
                } else {
                    interp.stack.emplace_back(result);
                }
            } else {
                throw std::runtime_error("Type error: ceil requires a numeric value");
            }
        });
        
        // round: Round to nearest integer
        interp.register_op("round", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on round");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer) {
                // Integer is already rounded
                interp.stack.push_back(a);
            } else if (a.type == WofType::Double) {
                // Round the double
                double val = std::get<double>(a.value);
                double result = std::round(val);
                
                // If the result is representable as an integer, convert it
                if (result <= static_cast<double>(std::numeric_limits<int64_t>::max()) &&
                    result >= static_cast<double>(std::numeric_limits<int64_t>::min())) {
                    interp.stack.emplace_back(static_cast<int64_t>(result));
                } else {
                    interp.stack.emplace_back(result);
                }
            } else {
                throw std::runtime_error("Type error: round requires a numeric value");
            }
        });
        
        // ----- Constants -----
        
        // pi: Push π onto the stack
        interp.register_op("pi", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(3.14159265358979323846);
        });
        
        // e: Push e onto the stack
        interp.register_op("e", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(2.71828182845904523536);
        });
    }
};

} // namespace woflang

// Plugin registration function
WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::MathOpsPlugin plugin;
    plugin.register_ops(interp);
}