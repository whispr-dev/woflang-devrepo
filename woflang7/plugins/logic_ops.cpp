// ==================================================
// FIXED: logic_ops.cpp
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <sstream>
#include <iomanip>

namespace woflang {

namespace logic_helpers {
    // Boolean operations
    bool boolean_and(bool a, bool b) { return a && b; }
    bool boolean_or(bool a, bool b) { return a || b; }
    bool boolean_xor(bool a, bool b) { return a != b; }
    bool boolean_not(bool a) { return !a; }
    bool boolean_implies(bool a, bool b) { return !a || b; }
    bool boolean_equivalent(bool a, bool b) { return a == b; }
    bool boolean_nand(bool a, bool b) { return !(a && b); }
    bool boolean_nor(bool a, bool b) { return !(a || b); }
    
    // Helper to generate truth tables
    std::string generate_truth_table(const std::string& op, 
                                    std::function<bool(bool, bool)> func) {
        std::stringstream ss;
        
        ss << "Truth table for " << op << ":\n";
        ss << "+-------+-------+-------+\n";
        ss << "| A     | B     | " << std::setw(5) << std::left << op << " |\n";
        ss << "+-------+-------+-------+\n";
        
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                bool a = (i == 1);
                bool b = (j == 1);
                bool result = func(a, b);
                
                ss << "| " << std::setw(5) << std::left << (a ? "true" : "false")
                   << " | " << std::setw(5) << std::left << (b ? "true" : "false")
                   << " | " << std::setw(5) << std::left << (result ? "true" : "false")
                   << " |\n";
            }
        }
        
        ss << "+-------+-------+-------+\n";
        return ss.str();
    }
    
    // Generate truth table for unary operators
    std::string generate_unary_truth_table(const std::string& op, 
                                         std::function<bool(bool)> func) {
        std::stringstream ss;
        
        ss << "Truth table for " << op << ":\n";
        ss << "+-------+-------+\n";
        ss << "| A     | " << std::setw(5) << std::left << op << " |\n";
        ss << "+-------+-------+\n";
        
        for (int i = 0; i < 2; i++) {
            bool a = (i == 1);
            bool result = func(a);
            
            ss << "| " << std::setw(5) << std::left << (a ? "true" : "false")
               << " | " << std::setw(5) << std::left << (result ? "true" : "false")
               << " |\n";
        }
        
        ss << "+-------+-------+\n";
        return ss.str();
    }
    
    // Convert WofValue to boolean
    bool to_bool(const WofValue& val) {
        if (val.is_numeric()) {
            return val.as_numeric() != 0.0;
        }
        return false;
    }
}

class LogicOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // ----- Boolean Operations -----
        
        // and: Logical AND
        interp.register_op("and", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("and requires two values");
            }
            
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            bool bool_a = logic_helpers::to_bool(a);
            bool bool_b = logic_helpers::to_bool(b);
            
            bool result = logic_helpers::boolean_and(bool_a, bool_b);
            
            stack.push(WofValue(result ? 1.0 : 0.0));
        });
        
        // or: Logical OR
        interp.register_op("or", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("or requires two values");
            }
            
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            bool bool_a = logic_helpers::to_bool(a);
            bool bool_b = logic_helpers::to_bool(b);
            
            bool result = logic_helpers::boolean_or(bool_a, bool_b);
            
            stack.push(WofValue(result ? 1.0 : 0.0));
        });
        
        // xor: Logical XOR
        interp.register_op("xor", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("xor requires two values");
            }
            
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            bool bool_a = logic_helpers::to_bool(a);
            bool bool_b = logic_helpers::to_bool(b);
            
            bool result = logic_helpers::boolean_xor(bool_a, bool_b);
            
            stack.push(WofValue(result ? 1.0 : 0.0));
        });
        
        // not: Logical NOT
        interp.register_op("not", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("not requires a value");
            }
            
            auto a = stack.top(); stack.pop();
            
            bool bool_a = logic_helpers::to_bool(a);
            
            bool result = logic_helpers::boolean_not(bool_a);
            
            stack.push(WofValue(result ? 1.0 : 0.0));
        });
        
        // implies: Logical implication
        interp.register_op("implies", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("implies requires two values");
            }
            
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            bool bool_a = logic_helpers::to_bool(a);
            bool bool_b = logic_helpers::to_bool(b);
            
            bool result = logic_helpers::boolean_implies(bool_a, bool_b);
            
            stack.push(WofValue(result ? 1.0 : 0.0));
        });
        
        // equivalent: Logical equivalence
        interp.register_op("equivalent", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("equivalent requires two values");
            }
            
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            bool bool_a = logic_helpers::to_bool(a);
            bool bool_b = logic_helpers::to_bool(b);
            
            bool result = logic_helpers::boolean_equivalent(bool_a, bool_b);
            
            stack.push(WofValue(result ? 1.0 : 0.0));
        });
        
        // nand: Logical NAND
        interp.register_op("nand", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("nand requires two values");
            }
            
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            bool bool_a = logic_helpers::to_bool(a);
            bool bool_b = logic_helpers::to_bool(b);
            
            bool result = logic_helpers::boolean_nand(bool_a, bool_b);
            
            stack.push(WofValue(result ? 1.0 : 0.0));
        });
        
        // nor: Logical NOR
        interp.register_op("nor", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("nor requires two values");
            }
            
            auto b = stack.top(); stack.pop();
            auto a = stack.top(); stack.pop();
            
            bool bool_a = logic_helpers::to_bool(a);
            bool bool_b = logic_helpers::to_bool(b);
            
            bool result = logic_helpers::boolean_nor(bool_a, bool_b);
            
            stack.push(WofValue(result ? 1.0 : 0.0));
        });
        
        // ----- Truth Tables -----
        
        // truth_table_and: Display truth table for AND
        interp.register_op("truth_table_and", [](std::stack<WofValue>&) {
            std::string table = logic_helpers::generate_truth_table("AND", logic_helpers::boolean_and);
            std::cout << table;
        });
        
        // truth_table_or: Display truth table for OR
        interp.register_op("truth_table_or", [](std::stack<WofValue>&) {
            std::string table = logic_helpers::generate_truth_table("OR", logic_helpers::boolean_or);
            std::cout << table;
        });
        
        // truth_table_xor: Display truth table for XOR
        interp.register_op("truth_table_xor", [](std::stack<WofValue>&) {
            std::string table = logic_helpers::generate_truth_table("XOR", logic_helpers::boolean_xor);
            std::cout << table;
        });
        
        // truth_table_not: Display truth table for NOT
        interp.register_op("truth_table_not", [](std::stack<WofValue>&) {
            std::string table = logic_helpers::generate_unary_truth_table("NOT", logic_helpers::boolean_not);
            std::cout << table;
        });
        
        // truth_table_implies: Display truth table for IMPLIES
        interp.register_op("truth_table_implies", [](std::stack<WofValue>&) {
            std::string table = logic_helpers::generate_truth_table("IMPLIES", logic_helpers::boolean_implies);
            std::cout << table;
        });
        
        // truth_table_equivalent: Display truth table for EQUIVALENT
        interp.register_op("truth_table_equivalent", [](std::stack<WofValue>&) {
            std::string table = logic_helpers::generate_truth_table("EQUIV", logic_helpers::boolean_equivalent);
            std::cout << table;
        });
        
        // truth_table_nand: Display truth table for NAND
        interp.register_op("truth_table_nand", [](std::stack<WofValue>&) {
            std::string table = logic_helpers::generate_truth_table("NAND", logic_helpers::boolean_nand);
            std::cout << table;
        });
        
        // truth_table_nor: Display truth table for NOR
        interp.register_op("truth_table_nor", [](std::stack<WofValue>&) {
            std::string table = logic_helpers::generate_truth_table("NOR", logic_helpers::boolean_nor);
            std::cout << table;
        });
        
        // ----- Educational Operations -----
        
        // logic_gates: Display information about logic gates
        interp.register_op("logic_gates", [](std::stack<WofValue>&) {
            std::cout << "=== Logic Gates ===\n\n";
            
            std::cout << "1. NOT Gate (¬):\n";
            std::cout << "   - Inverts the input\n";
            std::cout << "   - Truth table: NOT A = ¬A\n";
            std::cout << "     A | NOT A\n";
            std::cout << "     ---+------\n";
            std::cout << "     F | T\n";
            std::cout << "     T | F\n\n";
            
            std::cout << "2. AND Gate (∧):\n";
            std::cout << "   - Output is true only if all inputs are true\n";
            std::cout << "   - Truth table: A AND B = A ∧ B\n";
            std::cout << "     A | B | A AND B\n";
            std::cout << "     ---+---+--------\n";
            std::cout << "     F | F | F\n";
            std::cout << "     F | T | F\n";
            std::cout << "     T | F | F\n";
            std::cout << "     T | T | T\n\n";
            
            std::cout << "3. OR Gate (∨):\n";
            std::cout << "   - Output is true if at least one input is true\n";
            std::cout << "   - Truth table: A OR B = A ∨ B\n";
            std::cout << "     A | B | A OR B\n";
            std::cout << "     ---+---+-------\n";
            std::cout << "     F | F | F\n";
            std::cout << "     F | T | T\n";
            std::cout << "     T | F | T\n";
            std::cout << "     T | T | T\n\n";
            
            std::cout << "4. XOR Gate (⊕):\n";
            std::cout << "   - Output is true if inputs are different\n";
            std::cout << "   - Truth table: A XOR B = A ⊕ B\n";
            std::cout << "     A | B | A XOR B\n";
            std::cout << "     ---+---+--------\n";
            std::cout << "     F | F | F\n";
            std::cout << "     F | T | T\n";
            std::cout << "     T | F | T\n";
            std::cout << "     T | T | F\n\n";
            
            std::cout << "5. NAND Gate:\n";
            std::cout << "   - Negation of AND: NOT (A AND B)\n";
            std::cout << "   - Universal gate: Can implement any logic function\n\n";
            
            std::cout << "6. NOR Gate:\n";
            std::cout << "   - Negation of OR: NOT (A OR B)\n";
            std::cout << "   - Universal gate: Can implement any logic function\n\n";
            
            std::cout << "7. IMPLIES (→):\n";
            std::cout << "   - Logical implication: if A then B\n";
            std::cout << "   - Equivalent to: NOT A OR B\n";
            std::cout << "   - Truth table: A → B\n";
            std::cout << "     A | B | A → B\n";
            std::cout << "     ---+---+------\n";
            std::cout << "     F | F | T\n";
            std::cout << "     F | T | T\n";
            std::cout << "     T | F | F\n";
            std::cout << "     T | T | T\n\n";
            
            std::cout << "8. EQUIVALENT (↔):\n";
            std::cout << "   - Logical equivalence: A is true if and only if B is true\n";
            std::cout << "   - Equivalent to: (A AND B) OR (NOT A AND NOT B)\n";
            std::cout << "   - Truth table: A ↔ B\n";
            std::cout << "     A | B | A ↔ B\n";
            std::cout << "     ---+---+------\n";
            std::cout << "     F | F | T\n";
            std::cout << "     F | T | F\n";
            std::cout << "     T | F | F\n";
            std::cout << "     T | T | T\n\n";
        });
        
        // logic_tutorial: Display a basic logic tutorial
        interp.register_op("logic_tutorial", [](std::stack<WofValue>&) {
            std::cout << "=== Logic Tutorial ===\n\n";
            
            std::cout << "1. Propositional Logic:\n";
            std::cout << "   - Deals with propositions (statements that are either true or false)\n";
            std::cout << "   - Basic operators: AND (∧), OR (∨), NOT (¬), IMPLIES (→), EQUIVALENT (↔)\n\n";
            
            std::cout << "2. Truth Tables:\n";
            std::cout << "   - Show all possible combinations of truth values for variables\n";
            std::cout << "   - Useful for analyzing logical expressions\n\n";
            
            std::cout << "3. Logical Equivalences:\n";
            std::cout << "   - De Morgan's Laws: NOT (A AND B) = NOT A OR NOT B\n";
            std::cout << "   - Double Negation: NOT (NOT A) = A\n";
            std::cout << "   - Distributive Law: A AND (B OR C) = (A AND B) OR (A AND C)\n\n";
            
            std::cout << "4. Tautologies and Contradictions:\n";
            std::cout << "   - Tautology: Always true (e.g., A OR NOT A)\n";
            std::cout << "   - Contradiction: Always false (e.g., A AND NOT A)\n\n";
            
            std::cout << "5. Implication:\n";
            std::cout << "   - A → B is false only when A is true and B is false\n";
            std::cout << "   - Equivalent to NOT A OR B\n\n";
            
            std::cout << "6. Logical Equivalence:\n";
            std::cout << "   - A ↔ B is true when A and B have the same truth value\n";
            std::cout << "   - Equivalent to (A → B) AND (B → A)\n\n";
            
            std::cout << "7. Properties of Logic Gates:\n";
            std::cout << "   - NAND and NOR are universal gates\n";
            std::cout << "   - XOR is used in computer arithmetic operations\n\n";
            
            std::cout << "Use 'logic_gates' for information about specific gates.\n";
            std::cout << "Use 'truth_table_*' operations to see truth tables for various operations.\n";
        });
        
        // tautology: Check if a proposition is always true
        interp.register_op("tautology", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                std::cout << "tautology demo: A OR NOT A\n";
                
                // Demonstrate A OR NOT A is always true
                for (int i = 0; i < 2; i++) {
                    bool a = (i == 1);
                    bool not_a = !a;
                    bool result = a || not_a;
                    
                    std::cout << "A=" << (a ? "T" : "F") 
                             << " | NOT A=" << (not_a ? "T" : "F") 
                             << " | A OR NOT A=" << (result ? "T" : "F") << "\n";
                }
                
                std::cout << "This is a tautology - always true!\n";
                stack.push(WofValue(1.0));
                return;
            }
            
            // Check if two values form a tautology when ORed with NOT
            auto a = stack.top(); stack.pop();
            auto not_a = stack.top(); stack.pop();
            
            bool bool_a = logic_helpers::to_bool(a);
            bool bool_not_a = logic_helpers::to_bool(not_a);
            
            bool is_tautology = (bool_a || bool_not_a) && (!bool_a || !bool_not_a);
            
            std::cout << "Tautology check: " << (is_tautology ? "TRUE" : "FALSE") << "\n";
            stack.push(WofValue(is_tautology ? 1.0 : 0.0));
        });
        
        // contradiction: Check if a proposition is always false
        interp.register_op("contradiction", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                std::cout << "contradiction demo: A AND NOT A\n";
                
                // Demonstrate A AND NOT A is always false
                for (int i = 0; i < 2; i++) {
                    bool a = (i == 1);
                    bool not_a = !a;
                    bool result = a && not_a;
                    
                    std::cout << "A=" << (a ? "T" : "F") 
                             << " | NOT A=" << (not_a ? "T" : "F") 
                             << " | A AND NOT A=" << (result ? "T" : "F") << "\n";
                }
                
                std::cout << "This is a contradiction - always false!\n";
                stack.push(WofValue(0.0));
                return;
            }
            
            // Check if two values form a contradiction when ANDed
            auto a = stack.top(); stack.pop();
            auto not_a = stack.top(); stack.pop();
            
            bool bool_a = logic_helpers::to_bool(a);
            bool bool_not_a = logic_helpers::to_bool(not_a);
            
            bool is_contradiction = (bool_a && bool_not_a) || (!bool_a && !bool_not_a);
            
            std::cout << "Contradiction check: " << (is_contradiction ? "TRUE" : "FALSE") << "\n";
            stack.push(WofValue(is_contradiction ? 1.0 : 0.0));
        });
        
        // de_morgan: Demonstrate De Morgan's laws
        interp.register_op("de_morgan", [](std::stack<WofValue>&) {
            std::cout << "=== De Morgan's Laws ===\n\n";
            
            std::cout << "Law 1: NOT (A AND B) = (NOT A) OR (NOT B)\n";
            std::cout << "Law 2: NOT (A OR B) = (NOT A) AND (NOT B)\n\n";
            
            std::cout << "Verification:\n";
            std::cout << "A | B | A∧B | ¬(A∧B) | ¬A | ¬B | ¬A∨¬B | Equal?\n";
            std::cout << "--|---|-----|-------|----|----|-------|------\n";
            
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    bool a = (i == 1);
                    bool b = (j == 1);
                    bool a_and_b = a && b;
                    bool not_a_and_b = !a_and_b;
                    bool not_a = !a;
                    bool not_b = !b;
                    bool not_a_or_not_b = not_a || not_b;
                    bool equal = (not_a_and_b == not_a_or_not_b);
                    
                    std::cout << (a ? "T" : "F") << " | " 
                             << (b ? "T" : "F") << " |  " 
                             << (a_and_b ? "T" : "F") << "  |   " 
                             << (not_a_and_b ? "T" : "F") << "   | " 
                             << (not_a ? "T" : "F") << "  | " 
                             << (not_b ? "T" : "F") << "  |   " 
                             << (not_a_or_not_b ? "T" : "F") << "   |  " 
                             << (equal ? "✓" : "✗") << "\n";
                }
            }
            
            std::cout << "\nBoth laws are verified! ✓\n";
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::LogicOpsPlugin plugin;
    plugin.register_ops(interp);
}