// ==================================================
// FIXED: math_ops.cpp - Essential mathematical operations 
// ==================================================
#include "../../src/core/woflang.hpp"
#include <cmath>
#include <iostream>
#include <limits>

namespace woflang {

class MathOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // Basic Stack Operations
        interp.register_op("dup", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("Stack underflow on dup");
            }
            stack.push(stack.top());
        });
        
        interp.register_op("drop", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("Stack underflow on drop");
            }
            stack.pop();
        });
        
        interp.register_op("swap", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("Stack underflow on swap");
            }
            auto a = stack.top(); stack.pop();
            auto b = stack.top(); stack.pop();
            stack.push(a);
            stack.push(b);
        });
        
        // Arithmetic Operations
        interp.register_op("+", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("Stack underflow on +");
            }
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric() && b.is_numeric()) {
                stack.push(WofValue(a.as_numeric() + b.as_numeric()));
            } else {
                throw std::runtime_error("Type error: + requires numeric values");
            }
        });
        
        interp.register_op("-", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("Stack underflow on -");
            }
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric() && b.is_numeric()) {
                stack.push(WofValue(a.as_numeric() - b.as_numeric()));
            } else {
                throw std::runtime_error("Type error: - requires numeric values");
            }
        });
        
        interp.register_op("*", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("Stack underflow on *");
            }
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric() && b.is_numeric()) {
                stack.push(WofValue(a.as_numeric() * b.as_numeric()));
            } else {
                throw std::runtime_error("Type error: * requires numeric values");
            }
        });
        
        interp.register_op("/", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("Stack underflow on /");
            }
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric() && b.is_numeric()) {
                double b_val = b.as_numeric();
                if (b_val == 0.0) {
                    throw std::runtime_error("Division by zero");
                }
                stack.push(WofValue(a.as_numeric() / b_val));
            } else {
                throw std::runtime_error("Type error: / requires numeric values");
            }
        });
        
        // Power and roots
        interp.register_op("pow", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("Stack underflow on pow");
            }
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric() && b.is_numeric()) {
                double result = std::pow(a.as_numeric(), b.as_numeric());
                stack.push(WofValue(result));
            } else {
                throw std::runtime_error("Type error: pow requires numeric values");
            }
        });
        
        interp.register_op("sqrt", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("Stack underflow on sqrt");
            }
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric()) {
                double val = a.as_numeric();
                if (val < 0.0) {
                    throw std::runtime_error("Cannot take square root of negative value");
                }
                stack.push(WofValue(std::sqrt(val)));
            } else {
                throw std::runtime_error("Type error: sqrt requires a numeric value");
            }
        });
        
        // Trigonometric functions
        interp.register_op("sin", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("Stack underflow on sin");
            }
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric()) {
                stack.push(WofValue(std::sin(a.as_numeric())));
            } else {
                throw std::runtime_error("Type error: sin requires a numeric value");
            }
        });
        
        interp.register_op("cos", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("Stack underflow on cos");
            }
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric()) {
                stack.push(WofValue(std::cos(a.as_numeric())));
            } else {
                throw std::runtime_error("Type error: cos requires a numeric value");
            }
        });
        
        interp.register_op("tan", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("Stack underflow on tan");
            }
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric()) {
                stack.push(WofValue(std::tan(a.as_numeric())));
            } else {
                throw std::runtime_error("Type error: tan requires a numeric value");
            }
        });
        
        // Logarithmic functions
        interp.register_op("ln", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("Stack underflow on ln");
            }
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric()) {
                double val = a.as_numeric();
                if (val <= 0.0) {
                    throw std::runtime_error("Domain error: ln argument must be positive");
                }
                stack.push(WofValue(std::log(val)));
            } else {
                throw std::runtime_error("Type error: ln requires a numeric value");
            }
        });
        
        interp.register_op("log10", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("Stack underflow on log10");
            }
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric()) {
                double val = a.as_numeric();
                if (val <= 0.0) {
                    throw std::runtime_error("Domain error: log10 argument must be positive");
                }
                stack.push(WofValue(std::log10(val)));
            } else {
                throw std::runtime_error("Type error: log10 requires a numeric value");
            }
        });
        
        // Utility functions
        interp.register_op("abs", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("Stack underflow on abs");
            }
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric()) {
                stack.push(WofValue(std::abs(a.as_numeric())));
            } else {
                throw std::runtime_error("Type error: abs requires a numeric value");
            }
        });
        
        interp.register_op("floor", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("Stack underflow on floor");
            }
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric()) {
                stack.push(WofValue(std::floor(a.as_numeric())));
            } else {
                throw std::runtime_error("Type error: floor requires a numeric value");
            }
        });
        
        interp.register_op("ceil", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("Stack underflow on ceil");
            }
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric()) {
                stack.push(WofValue(std::ceil(a.as_numeric())));
            } else {
                throw std::runtime_error("Type error: ceil requires a numeric value");
            }
        });
        
        // Constants
        interp.register_op("pi", [](std::stack<WofValue>& stack) {
            stack.push(WofValue(M_PI));
        });
        
        interp.register_op("e", [](std::stack<WofValue>& stack) {
            stack.push(WofValue(M_E));
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::MathOpsPlugin plugin;
    plugin.register_ops(interp);
}