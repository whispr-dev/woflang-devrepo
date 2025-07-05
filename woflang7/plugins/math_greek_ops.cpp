// ==================================================
// FIXED: math_greek_ops.cpp
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <cmath>
#include <limits>

namespace woflang {

class MathGreekPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // π (pi) - Mathematical constant
        interp.register_op("π", [](std::stack<WofValue>& stack) {
            stack.push(WofValue(M_PI));
            std::cout << "π = " << M_PI << "\n";
        });
        
        // Σ (sigma) - Summation
        interp.register_op("Σ", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "Σ: Stack is empty\n";
                return;
            }
            
            double sum = 0.0;
            while (!stack.empty()) {
                auto val = stack.top(); stack.pop();
                if (val.is_numeric()) {
                    sum += val.as_numeric();
                }
            }
            
            stack.push(WofValue(sum));
            std::cout << "Σ = " << sum << "\n";
        });
        
        // Π (pi) - Product
        interp.register_op("Π", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "Π: Stack is empty\n";
                return;
            }
            
            double product = 1.0;
            while (!stack.empty()) {
                auto val = stack.top(); stack.pop();
                if (val.is_numeric()) {
                    product *= val.as_numeric();
                }
            }
            
            stack.push(WofValue(product));
            std::cout << "Π = " << product << "\n";
        });
        
        // Δ (delta) - Difference
        interp.register_op("Δ", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                std::cout << "Δ: Need at least 2 values\n";
                return;
            }
            
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            if (a.is_numeric() && b.is_numeric()) {
                double delta = std::abs(a.as_numeric() - b.as_numeric());
                stack.push(WofValue(delta));
                std::cout << "Δ = " << delta << "\n";
            } else {
                std::cout << "Δ: Requires numeric values\n";
            }
        });
        
        // σ (sigma) - Standard deviation (simplified)
        interp.register_op("σ", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "σ: Stack is empty\n";
                return;
            }
            
            std::vector<double> values;
            while (!stack.empty()) {
                auto val = stack.top(); stack.pop();
                if (val.is_numeric()) {
                    values.push_back(val.as_numeric());
                }
            }
            
            if (values.empty()) {
                std::cout << "σ: No numeric values\n";
                return;
            }
            
            // Calculate mean
            double mean = 0.0;
            for (double v : values) {
                mean += v;
            }
            mean /= values.size();
            
            // Calculate variance
            double variance = 0.0;
            for (double v : values) {
                variance += (v - mean) * (v - mean);
            }
            variance /= values.size();
            
            // Standard deviation
            double std_dev = std::sqrt(variance);
            
            stack.push(WofValue(std_dev));
            std::cout << "σ = " << std_dev << "\n";
        });
        
        // √ (square root)
        interp.register_op("√", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "√: Stack underflow\n";
                return;
            }
            
            auto val = stack.top(); stack.pop();
            if (val.is_numeric()) {
                double x = val.as_numeric();
                if (x >= 0) {
                    double result = std::sqrt(x);
                    stack.push(WofValue(result));
                    std::cout << "√" << x << " = " << result << "\n";
                } else {
                    std::cout << "√: Cannot take square root of negative number\n";
                }
            } else {
                std::cout << "√: Requires numeric value\n";
            }
        });
        
        // ∛ (cube root)
        interp.register_op("∛", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                std::cout << "∛: Stack underflow\n";
                return;
            }
            
            auto val = stack.top(); stack.pop();
            if (val.is_numeric()) {
                double x = val.as_numeric();
                double result = std::cbrt(x);
                stack.push(WofValue(result));
                std::cout << "∛" << x << " = " << result << "\n";
            } else {
                std::cout << "∛: Requires numeric value\n";
            }
        });
        
        // ∞ (infinity)
        interp.register_op("∞", [](std::stack<WofValue>& stack) {
            stack.push(WofValue(std::numeric_limits<double>::infinity()));
            std::cout << "∞: Infinity pushed to stack\n";
        });
        
        // ∅ (empty set / void)
        interp.register_op("∅", [](std::stack<WofValue>& stack) {
            std::cout << "∅: The void consumes all. Stack cleared.\n";
            while (!stack.empty()) stack.pop();
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::MathGreekPlugin plugin;
    plugin.register_ops(interp);
}