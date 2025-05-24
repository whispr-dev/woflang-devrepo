WOFLANG_PLUGIN_EXPORT void register_plugin(WoflangInterpreter& interp) {
    static CryptoOpsPlugin plugin;
    plugin.register_ops(interp);
}
ops_symbolic_simplify_rules.cpp (Fixed)
cpp#include "../../src/core/woflang.hpp"
#include <iostream>

// Simple pattern-based symbolic simplification rules plugin
class SymbolicSimplifyRulesPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("simplify_sum", [](WoflangInterpreter& interp) {
            // Rule: X + X -> 2 * X
            if (interp.stack.size() < 3) return;
            
            auto c = interp.stack.back(); 
            interp.stack.pop_back();
            
            auto b = interp.stack.back(); 
            interp.stack.pop_back();
            
            auto a = interp.stack.back(); 
            interp.stack.pop_back();

            // Check all types first
            if (a.type != WofType::Symbol || b.type != WofType::Symbol || c.type != WofType::String) {
                // Push back and return
                interp.stack.push_back(a);
                interp.stack.push_back(b);
                interp.stack.push_back(c);
                return;
            }

            // Check X + X pattern
            std::string a_str = std::get<std::string>(a.value);
            std::string b_str = std::get<std::string>(b.value);
            std::string c_str = std::get<std::string>(c.value);
            
            if (a_str == b_str && c_str == "+") {
                interp.stack.emplace_back(2);        // 2
                interp.stack.push_back(a);           // X
                interp.stack.emplace_back("*", WofType::String); // *
            } else {
                interp.stack.push_back(a);
                interp.stack.push_back(b);
                interp.stack.push_back(c);
            }
        });

        // Add more: X*1, X+0, etc.
        interp.register_op("simplify_mul_one", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 3) return;
            
            auto c = interp.stack.back(); 
            interp.stack.pop_back();
            
            auto b = interp.stack.back(); 
            interp.stack.pop_back();
            
            auto a = interp.stack.back(); 
            interp.stack.pop_back();

            // Rule: X * 1 => X
            if (a.type == WofType::Symbol && 
                b.type == WofType::Integer && 
                std::get<int64_t>(b.value) == 1 &&
                c.type == WofType::String && 
                std::get<std::string>(c.value) == "*") {
                
                interp.stack.push_back(a);
            } else {
                interp.stack.push_back(a);
                interp.stack.push_back(b);
                interp.stack.push_back(c);
            }
        });
    }
};


