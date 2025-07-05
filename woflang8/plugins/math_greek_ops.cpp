// ==================================================
// FIXED: math_greek_ops.cpp  
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <cmath>
#include <limits>

extern "C" {

void init_plugin(woflang::WoflangInterpreter::OpTable* op_table) {
    // π (pi) - Mathematical constant
    (*op_table)["π"] = [](std::stack<woflang::WofValue>& stack) {
        woflang::WofValue val;
        val.d = M_PI;
        stack.push(val);
        std::cout << "π = " << M_PI << "\n";
    };
    
    // Σ (sigma) - Summation
    (*op_table)["Σ"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            std::cout << "Σ: Stack is empty\n";
            return;
        }
        
        double sum = 0.0;
        while (!stack.empty()) {
            auto val = stack.top(); stack.pop();
            sum += val.d;
        }
        
        woflang::WofValue result;
        result.d = sum;
        stack.push(result);
        std::cout << "Σ = " << sum << "\n";
    };
    
    // Π (pi) - Product
    (*op_table)["Π"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            std::cout << "Π: Stack is empty\n";
            return;
        }
        
        double product = 1.0;
        while (!stack.empty()) {
            auto val = stack.top(); stack.pop();
            product *= val.d;
        }
        
        woflang::WofValue result;
        result.d = product;
        stack.push(result);
        std::cout << "Π = " << product << "\n";
    };
    
    // Δ (delta) - Difference
    (*op_table)["Δ"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.size() < 2) {
            std::cout << "Δ: Need at least 2 values\n";
            return;
        }
        
        auto b = stack.top(); stack.pop();
        auto a = stack.top(); stack.pop();
        
        double delta = std::abs(a.d - b.d);
        woflang::WofValue result;
        result.d = delta;
        stack.push(result);
        std::cout << "Δ = " << delta << "\n";
    };
    
    // σ (sigma) - Standard deviation (simplified)
    (*op_table)["σ"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            std::cout << "σ: Stack is empty\n";
            return;
        }
        
        std::vector<double> values;
        while (!stack.empty()) {
            auto val = stack.top(); stack.pop();
            values.push_back(val.d);
        }
        
        if (values.empty()) {
            std::cout << "σ: No values\n";
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
        
        woflang::WofValue result;
        result.d = std_dev;
        stack.push(result);
        std::cout << "σ = " << std_dev << "\n";
    };
    
    // √ (square root)
    (*op_table)["√"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            std::cout << "√: Stack underflow\n";
            return;
        }
        
        auto val = stack.top(); stack.pop();
        double x = val.d;
        if (x >= 0) {
            double result = std::sqrt(x);
            woflang::WofValue res;
            res.d = result;
            stack.push(res);
            std::cout << "√" << x << " = " << result << "\n";
        } else {
            std::cout << "√: Cannot take square root of negative number\n";
        }
    };
    
    // ∛ (cube root)
    (*op_table)["∛"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            std::cout << "∛: Stack underflow\n";
            return;
        }
        
        auto val = stack.top(); stack.pop();
        double x = val.d;
        double result = std::cbrt(x);
        woflang::WofValue res;
        res.d = result;
        stack.push(res);
        std::cout << "∛" << x << " = " << result << "\n";
    };
    
    // ∞ (infinity)
    (*op_table)["∞"] = [](std::stack<woflang::WofValue>& stack) {
        woflang::WofValue val;
        val.d = std::numeric_limits<double>::infinity();
        stack.push(val);
        std::cout << "∞: Infinity pushed to stack\n";
    };
    
    // ∅ (empty set / void)
    (*op_table)["∅"] = [](std::stack<woflang::WofValue>& stack) {
        std::cout << "∅: The void consumes all. Stack cleared.\n";
        while (!stack.empty()) stack.pop();
    };
}

} // extern "C"

