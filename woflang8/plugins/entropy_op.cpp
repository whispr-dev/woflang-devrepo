// ==================================================
// FIXED: entropy_op.cpp
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <map>

extern "C" {

void init_plugin(woflang::WoflangInterpreter::OpTable* op_table) {
    (*op_table)["entropy"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            std::cout << "The void has no entropy. Only chaos remains.\n";
            return;
        }
        
        // Calculate Shannon entropy of the stack
        std::map<double, int> counts;
        double total = 0;
        
        // Copy stack to vector to analyze without destroying
        std::vector<woflang::WofValue> values;
        std::stack<woflang::WofValue> temp_stack = stack;
        while (!temp_stack.empty()) {
            values.push_back(temp_stack.top());
            temp_stack.pop();
        }
        
        for (const auto& val : values) {
            counts[val.d]++;
            total++;
        }
        
        double entropy = 0.0;
        for (const auto& [_, count] : counts) {
            double p = count / total;
            entropy -= p * std::log2(p);
        }
        
        std::cout << "Stack entropy: " << entropy << " bits\n";
        std::cout << "The universe tends toward maximum entropy...\n";
        
        woflang::WofValue result;
        result.d = entropy;
        stack.push(result);
    };
    
    (*op_table)["chaos"] = [](std::stack<woflang::WofValue>& stack) {
        static std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
        
        // Generate chaotic values
        std::uniform_real_distribution<> dis(0.0, 1.0);
        double chaos_value = dis(gen);
        
        std::cout << "From chaos, order emerges: " << chaos_value << "\n";
        
        // Randomly shuffle the stack
        if (stack.size() > 1) {
            std::vector<woflang::WofValue> values;
            while (!stack.empty()) {
                values.push_back(stack.top());
                stack.pop();
            }
            std::shuffle(values.begin(), values.end(), gen);
            for (auto& val : values) {
                stack.push(val);
            }
            std::cout << "The stack has been touched by chaos.\n";
        }
        
        woflang::WofValue result;
        result.d = chaos_value;
        stack.push(result);
    };
}

} // extern "C"

// ==================================================
// FIXED: void_division_op.cpp
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <limits>

extern "C" {

void init_plugin(woflang::WoflangInterpreter::OpTable* op_table) {
    (*op_table)["void_division"] = [](std::stack<woflang::WofValue>& stack) {
        std::cout << "⚠️  FORBIDDEN OPERATION DETECTED ⚠️\n";
        std::cout << "Attempting to divide by the void...\n";
        
        if (stack.size() < 2) {
            std::cout << "The void requires a sacrifice.\n";
            return;
        }
        
        auto divisor = stack.top(); stack.pop();
        auto dividend = stack.top(); stack.pop();
        
        std::cout << "Dividing " << dividend.d 
                 << " by the essence of nothingness...\n";
        
        // The void consumes all
        while (!stack.empty()) stack.pop();
        
        // But leaves behind infinity
        woflang::WofValue result;
        result.d = std::numeric_limits<double>::infinity();
        stack.push(result);
        
        std::cout << "The operation succeeds. Infinity remains.\n";
        std::cout << "You have gazed into the abyss.\n";
    };
    
    (*op_table)["/0"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            std::cout << "Even the void requires something to consume.\n";
            return;
        }
        
        auto value = stack.top(); stack.pop();
        
        std::cout << "÷0: " << value.d << " → ∞\n";
        woflang::WofValue result;
        result.d = std::numeric_limits<double>::infinity();
        stack.push(result);
    };
}

} // extern "C"