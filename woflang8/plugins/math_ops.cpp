// ==================================================
// 3. math_ops.cpp - Essential Mathematical Operations
// ==================================================
#include "../../src/core/woflang.hpp"
#include <cmath>
#include <iostream>
#include <limits>

extern "C" {

void init_plugin(woflang::WoflangInterpreter::OpTable* op_table) {
    // Basic Stack Operations
    (*op_table)["dup"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on dup");
        }
        stack.push(stack.top());
    };
    
    (*op_table)["drop"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on drop");
        }
        stack.pop();
    };
    
    (*op_table)["swap"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.size() < 2) {
            throw std::runtime_error("Stack underflow on swap");
        }
        auto a = stack.top(); stack.pop();
        auto b = stack.top(); stack.pop();
        stack.push(a);
        stack.push(b);
    };
    
    // Arithmetic Operations
    (*op_table)["+"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.size() < 2) {
            throw std::runtime_error("Stack underflow on +");
        }
        auto b = stack.top(); stack.pop();
        auto a = stack.top(); stack.pop();
        
        woflang::WofValue result;
        result.d = a.d + b.d;
        stack.push(result);
    };
    
    (*op_table)["-"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.size() < 2) {
            throw std::runtime_error("Stack underflow on -");
        }
        auto b = stack.top(); stack.pop();
        auto a = stack.top(); stack.pop();
        
        woflang::WofValue result;
        result.d = a.d - b.d;
        stack.push(result);
    };
    
    (*op_table)["*"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.size() < 2) {
            throw std::runtime_error("Stack underflow on *");
        }
        auto b = stack.top(); stack.pop();
        auto a = stack.top(); stack.pop();
        
        woflang::WofValue result;
        result.d = a.d * b.d;
        stack.push(result);
    };
    
    (*op_table)["/"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.size() < 2) {
            throw std::runtime_error("Stack underflow on /");
        }
        auto b = stack.top(); stack.pop();
        auto a = stack.top(); stack.pop();
        
        if (b.d == 0.0) {
            throw std::runtime_error("Division by zero");
        }
        
        woflang::WofValue result;
        result.d = a.d / b.d;
        stack.push(result);
    };
    
    // Power and roots
    (*op_table)["pow"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.size() < 2) {
            throw std::runtime_error("Stack underflow on pow");
        }
        auto b = stack.top(); stack.pop();
        auto a = stack.top(); stack.pop();
        
        woflang::WofValue result;
        result.d = std::pow(a.d, b.d);
        stack.push(result);
    };
    
    (*op_table)["sqrt"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on sqrt");
        }
        auto a = stack.top(); stack.pop();
        
        if (a.d < 0.0) {
            throw std::runtime_error("Cannot take square root of negative value");
        }
        
        woflang::WofValue result;
        result.d = std::sqrt(a.d);
        stack.push(result);
    };
    
    // Trigonometric functions
    (*op_table)["sin"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on sin");
        }
        auto a = stack.top(); stack.pop();
        
        woflang::WofValue result;
        result.d = std::sin(a.d);
        stack.push(result);
    };
    
    (*op_table)["cos"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on cos");
        }
        auto a = stack.top(); stack.pop();
        
        woflang::WofValue result;
        result.d = std::cos(a.d);
        stack.push(result);
    };
    
    (*op_table)["tan"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on tan");
        }
        auto a = stack.top(); stack.pop();
        
        woflang::WofValue result;
        result.d = std::tan(a.d);
        stack.push(result);
    };
    
    // Logarithmic functions
    (*op_table)["ln"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on ln");
        }
        auto a = stack.top(); stack.pop();
        
        if (a.d <= 0.0) {
            throw std::runtime_error("Domain error: ln argument must be positive");
        }
        
        woflang::WofValue result;
        result.d = std::log(a.d);
        stack.push(result);
    };
    
    (*op_table)["log10"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on log10");
        }
        auto a = stack.top(); stack.pop();
        
        if (a.d <= 0.0) {
            throw std::runtime_error("Domain error: log10 argument must be positive");
        }
        
        woflang::WofValue result;
        result.d = std::log10(a.d);
        stack.push(result);
    };
    
    // Utility functions
    (*op_table)["abs"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on abs");
        }
        auto a = stack.top(); stack.pop();
        
        woflang::WofValue result;
        result.d = std::abs(a.d);
        stack.push(result);
    };
    
    (*op_table)["floor"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on floor");
        }
        auto a = stack.top(); stack.pop();
        
        woflang::WofValue result;
        result.d = std::floor(a.d);
        stack.push(result);
    };
    
    (*op_table)["ceil"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow on ceil");
        }
        auto a = stack.top(); stack.pop();
        
        woflang::WofValue result;
        result.d = std::ceil(a.d);
        stack.push(result);
    };
    
    // Constants
    (*op_table)["pi"] = [](std::stack<woflang::WofValue>& stack) {
        woflang::WofValue result;
        result.d = M_PI;
        stack.push(result);
    };
    
    (*op_table)["e"] = [](std::stack<woflang::WofValue>& stack) {
        woflang::WofValue result;
        result.d = M_E;
        stack.push(result);
    };
}

} // extern "C"
