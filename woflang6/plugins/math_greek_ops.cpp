// plugins/math_greek_ops.cpp - Fixed Greek operations
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <cmath>

namespace woflang {

class MathGreekPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // π (pi) - Mathematical constant
        interp.register_op("π", [](WoflangInterpreter& interp) {
            interp.push(WofValue(M_PI));
            std::cout << "π = " << M_PI << "\n";
        });
        
        // Σ (sigma) - Summation
        interp.register_op("Σ", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "Σ: Stack is empty\n";
                return;
            }
            
            double sum = 0.0;
            while (!interp.stack.empty()) {
                auto val = interp.pop();
                if (val.is_numeric()) {
                    sum += val.as_numeric();
                }
            }
            
            interp.push(WofValue(sum));
            std::cout << "Σ = " << sum << "\n";
        });
        
        // Π (pi) - Product
        interp.register_op("Π", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "Π: Stack is empty\n";
                return;
            }
            
            double product = 1.0;
            while (!interp.stack.empty()) {
                auto val = interp.pop();
                if (val.is_numeric()) {
                    product *= val.as_numeric();
                }
            }
            
            interp.push(WofValue(product));
            std::cout << "Π = " << product << "\n";
        });
        
        // Δ (delta) - Difference
        interp.register_op("Δ", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                std::cout << "Δ: Need at least 2 values\n";
                return;
            }
            
            auto b = interp.pop();
            auto a = interp.pop();
            
            if (a.is_numeric() && b.is_numeric()) {
                double delta = std::abs(a.as_numeric() - b.as_numeric());
                interp.push(WofValue(delta));
                std::cout << "Δ = " << delta << "\n";
            } else {
                std::cout << "Δ: Requires numeric values\n";
            }
        });
        
        // σ (sigma) - Standard deviation (simplified)
        interp.register_op("σ", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "σ: Stack is empty\n";
                return;
            }
            
            std::vector<double> values;
            while (!interp.stack.empty()) {
                auto val = interp.pop();
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
            
            interp.push(WofValue(std_dev));
            std::cout << "σ = " << std_dev << "\n";
        });
        
        // √ (square root)
        interp.register_op("√", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "√: Stack underflow\n";
                return;
            }
            
            auto val = interp.pop();
            if (val.is_numeric()) {
                double x = val.as_numeric();
                if (x >= 0) {
                    double result = std::sqrt(x);
                    interp.push(WofValue(result));
                    std::cout << "√" << x << " = " << result << "\n";
                } else {
                    std::cout << "√: Cannot take square root of negative number\n";
                }
            } else {
                std::cout << "√: Requires numeric value\n";
            }
        });
        
        // ∛ (cube root)
        interp.register_op("∛", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                std::cout << "∛: Stack underflow\n";
                return;
            }
            
            auto val = interp.pop();
            if (val.is_numeric()) {
                double x = val.as_numeric();
                double result = std::cbrt(x);
                interp.push(WofValue(result));
                std::cout << "∛" << x << " = " << result << "\n";
            } else {
                std::cout << "∛: Requires numeric value\n";
            }
        });
        
        // ∞ (infinity)
        interp.register_op("∞", [](WoflangInterpreter& interp) {
            interp.push(WofValue(std::numeric_limits<double>::infinity()));
            std::cout << "∞: Infinity pushed to stack\n";
        });
        
        // ∅ (empty set / void)
        interp.register_op("∅", [](WoflangInterpreter& interp) {
            std::cout << "∅: The void consumes all. Stack cleared.\n";
            interp.clear_stack();
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::MathGreekPlugin plugin;
    plugin.register_ops(interp);
}

// Fixed include paths for plugins
// All plugins should use: #include "../../src/core/woflang.hpp"
// This ensures they can find the core headers from the plugins directory

// Common fixes needed:
// 1. Fix include paths in all plugins
// 2. Add missing #include <limits> for std::numeric_limits
// 3. Fix any duplicate operation registrations
// 4. Ensure all plugins use the WOFLANG_PLUGIN_EXPORT macro correctly