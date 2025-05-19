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

/**
 * @brief Helper functions and data for logic operations
 */
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
        
        // Header
        ss << "Truth table for " << op << ":\n";
        ss << "+-------+-------+-------+\n";
        ss << "| A     | B     | " << std::setw(5) << std::left << op << " |\n";
        ss << "+-------+-------+-------+\n";
        
        // Rows
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
        
        // Header
        ss << "Truth table for " << op << ":\n";
        ss << "+-------+-------+\n";
        ss << "| A     | " << std::setw(5) << std::left << op << " |\n";
        ss << "+-------+-------+\n";
        
        // Rows
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
    
    // Structure for a propositional logic expression
    struct LogicExpression {
        // Expression type
        enum class Type {
            Constant,   // True or False
            Variable,   // A named variable
            Not,        // Negation
            And,        // Conjunction
            Or,         // Disjunction
            Implies,    // Implication
            Equivalent  // Equivalence
        };
        
        Type type;                            // Expression type
        bool value;                           // For constants
        std::string name;                     // For variables
        std::shared_ptr<LogicExpression> left;  // For unary and binary operators (left operand)
        std::shared_ptr<LogicExpression> right; // For binary operators (right operand)
        
        // Create a constant expression
        static std::shared_ptr<LogicExpression> constant(bool val) {
            auto expr = std::make_shared<LogicExpression>();
            expr->type = Type::Constant;
            expr->value = val;
            return expr;
        }
        
        // Create a variable expression
        static std::shared_ptr<LogicExpression> variable(const std::string& var_name) {
            auto expr = std::make_shared<LogicExpression>();
            expr->type = Type::Variable;
            expr->name = var_name;
            return expr;
        }
        
        // Create a NOT expression
        static std::shared_ptr<LogicExpression> not_expr(std::shared_ptr<LogicExpression> operand) {
            auto expr = std::make_shared<LogicExpression>();
            expr->type = Type::Not;
            expr->left = operand;
            return expr;
        }
        
        // Create an AND expression
        static std::shared_ptr<LogicExpression> and_expr(std::shared_ptr<LogicExpression> left_op,
                                                      std::shared_ptr<LogicExpression> right_op) {
            auto expr = std::make_shared<LogicExpression>();
            expr->type = Type::And;
            expr->left = left_op;
            expr->right = right_op;
            return expr;
        }
        
        // Create an OR expression
        static std::shared_ptr<LogicExpression> or_expr(std::shared_ptr<LogicExpression> left_op,
                                                     std::shared_ptr<LogicExpression> right_op) {
            auto expr = std::make_shared<LogicExpression>();
            expr->type = Type::Or;
            expr->left = left_op;
            expr->right = right_op;
            return expr;
        }
        
        // Create an IMPLIES expression
        static std::shared_ptr<LogicExpression> implies_expr(std::shared_ptr<LogicExpression> left_op,
                                                          std::shared_ptr<LogicExpression> right_op) {
            auto expr = std::make_shared<LogicExpression>();
            expr->type = Type::Implies;
            expr->left = left_op;
            expr->right = right_op;
            return expr;
        }
        
        // Create an EQUIVALENT expression
        static std::shared_ptr<LogicExpression> equivalent_expr(std::shared_ptr<LogicExpression> left_op,
                                                             std::shared_ptr<LogicExpression> right_op) {
            auto expr = std::make_shared<LogicExpression>();
            expr->type = Type::Equivalent;
            expr->left = left_op;
            expr->right = right_op;
            return expr;
        }
        
        // Evaluate the expression with variable assignments
        bool evaluate(const std::map<std::string, bool>& variables) const {
            switch (type) {
                case Type::Constant:
                    return value;
                
                case Type::Variable:
                    if (variables.find(name) == variables.end()) {
                        throw std::runtime_error("Variable not assigned: " + name);
                    }
                    return variables.at(name);
                
                case Type::Not:
                    return !left->evaluate(variables);
                
                case Type::And:
                    return left->evaluate(variables) && right->evaluate(variables);
                
                case Type::Or:
                    return left->evaluate(variables) || right->evaluate(variables);
                
                case Type::Implies:
                    return !left->evaluate(variables) || right->evaluate(variables);
                
                case Type::Equivalent:
                    return left->evaluate(variables) == right->evaluate(variables);
                
                default:
                    throw std::runtime_error("Unknown expression type");
            }
        }
        
        // Get a string representation of the expression
        std::string to_string() const {
            switch (type) {
                case Type::Constant:
                    return value ? "true" : "false";
                
                case Type::Variable:
                    return name;
                
                case Type::Not:
                    return "¬(" + left->to_string() + ")";
                
                case Type::And:
                    return "(" + left->to_string() + " ∧ " + right->to_string() + ")";
                
                case Type::Or:
                    return "(" + left->to_string() + " ∨ " + right->to_string() + ")";
                
                case Type::Implies:
                    return "(" + left->to_string() + " → " + right->to_string() + ")";
                
                case Type::Equivalent:
                    return "(" + left->to_string() + " ↔ " + right->to_string() + ")";
                
                default:
                    return "Unknown";
            }
        }
        
        // Get all variables used in the expression
        std::set<std::string> get_variables() const {
            std::set<std::string> vars;
            
            switch (type) {
                case Type::Constant:
                    break;
                
                case Type::Variable:
                    vars.insert(name);
                    break;
                
                case Type::Not:
                    vars = left->get_variables();
                    break;
                
                case Type::And:
                case Type::Or:
                case Type::Implies:
                case Type::Equivalent:
                    vars = left->get_variables();
                    auto right_vars = right->get_variables();
                    vars.insert(right_vars.begin(), right_vars.end());
                    break;
            }
            
            return vars;
        }
        
        // Generate a truth table for the expression
        std::string truth_table() const {
            std::stringstream ss;
            
            // Get all variables
            std::set<std::string> vars = get_variables();
            std::vector<std::string> var_names(vars.begin(), vars.end());
            
            // Sort variable names for consistent output
            std::sort(var_names.begin(), var_names.end());
            
            // Header
            ss << "Truth table for: " << to_string() << "\n";
            ss << "+";
            for (size_t i = 0; i < var_names.size(); i++) {
                ss << "-------+";
            }
            ss << "-------+\n";
            
            ss << "| ";
            for (const auto& var : var_names) {
                ss << std::setw(5) << std::left << var << " | ";
            }
            ss << "Result |\n";
            
            ss << "+";
            for (size_t i = 0; i < var_names.size(); i++) {
                ss << "-------+";
            }
            ss << "-------+\n";
            
            // Generate all possible variable assignments
            int num_rows = 1 << var_names.size();
            
            for (int i = 0; i < num_rows; i++) {
                std::map<std::string, bool> assignment;
                
                // Set variable values based on bits of i
                for (size_t j = 0; j < var_names.size(); j++) {
                    bool value = (i & (1 << j)) != 0;
                    assignment[var_names[j]] = value;
                }
                
                // Evaluate the expression
                bool result = evaluate(assignment);
                
                // Print the row
                ss << "| ";
                for (const auto& var : var_names) {
                    ss << std::setw(5) << std::left << (assignment[var] ? "true" : "false") << " | ";
                }
                ss << std::setw(5) << std::left << (result ? "true" : "false") << " |\n";
            }
            
            ss << "+";
            for (size_t i = 0; i < var_names.size(); i++) {
                ss << "-------+";
            }
            ss << "-------+\n";
            
            return ss.str();
        }
    };
    
    // Simple parser for logic expressions
    class LogicParser {
    public:
        LogicParser(const std::string& expr) : expression(expr), pos(0) {
            // Replace logical symbols with their text equivalents for easier parsing
            replace_symbols();
        }
        
        std::shared_ptr<LogicExpression> parse() {
            auto result = parse_equivalence();
            
            // Check if we've parsed the entire expression
            skip_whitespace();
            if (pos < expression.size()) {
                throw std::runtime_error("Unexpected token: " + expression.substr(pos));
            }
            
            return result;
        }
        
    private:
        std::string expression;
        size_t pos;
        
        // Replace logical symbols with their text equivalents
        void replace_symbols() {
            std::map<std::string, std::string> replacements = {
                {"¬", "NOT "},
                {"∧", " AND "},
                {"∨", " OR "},
                {"→", " IMPLIES "},
                {"↔", " EQUIVALENT "},
                {"⇒", " IMPLIES "},
                {"⇔", " EQUIVALENT "},
                {"⊕", " XOR "},
                {"!", "NOT "},
                {"&&", " AND "},
                {"||", " OR "},
                {"=>", " IMPLIES "},
                {"<=>", " EQUIVALENT "},
                {"^", " XOR "}
            };
            
            for (const auto& [symbol, replacement] : replacements) {
                size_t pos = 0;
                while ((pos = expression.find(symbol, pos)) != std::string::npos) {
                    expression.replace(pos, symbol.length(), replacement);
                    pos += replacement.length();
                }
            }
        }
        
        // Skip whitespace characters
        void skip_whitespace() {
            while (pos < expression.size() && std::isspace(expression[pos])) {
                pos++;
            }
        }
        
        // Parse a primary expression (constants, variables, or parenthesized expressions)
        std::shared_ptr<LogicExpression> parse_primary() {
            skip_whitespace();
            
            // Check for end of expression
            if (pos >= expression.size()) {
                throw std::runtime_error("Unexpected end of expression");
            }
            
            // Check for constants
            if (expression.substr(pos, 4) == "true") {
                pos += 4;
                return LogicExpression::constant(true);
            }
            
            if (expression.substr(pos, 5) == "false") {
                pos += 5;
                return LogicExpression::constant(false);
            }
            
            // Check for NOT operator
            if (expression.substr(pos, 3) == "NOT") {
                pos += 3;
                skip_whitespace();
                return LogicExpression::not_expr(parse_primary());
            }
            
            // Check for parenthesized expressions
            if (expression[pos] == '(') {
                pos++;
                auto expr = parse_equivalence();
                
                skip_whitespace();
                if (pos >= expression.size() || expression[pos] != ')') {
                    throw std::runtime_error("Missing closing parenthesis");
                }
                
                pos++;
                return expr;
            }
            
            // Must be a variable
            std::string var_name;
            while (pos < expression.size() && (std::isalnum(expression[pos]) || expression[pos] == '_')) {
                var_name += expression[pos];
                pos++;
            }
            
            if (var_name.empty()) {
                throw std::runtime_error("Expected variable name, got: " + expression.substr(pos));
            }
            
            return LogicExpression::variable(var_name);
        }
        
        // Parse AND expressions
        std::shared_ptr<LogicExpression> parse_and() {
            auto left = parse_primary();
            
            while (true) {
                skip_whitespace();
                
                if (pos + 3 <= expression.size() && expression.substr(pos, 3) == "AND") {
                    pos += 3;
                    auto right = parse_primary();
                    left = LogicExpression::and_expr(left, right);
                } else {
                    break;
                }
            }
            
            return left;
        }
        
        // Parse OR expressions
        std::shared_ptr<LogicExpression> parse_or() {
            auto left = parse_and();
            
            while (true) {
                skip_whitespace();
                
                if (pos + 2 <= expression.size() && expression.substr(pos, 2) == "OR") {
                    pos += 2;
                    auto right = parse_and();
                    left = LogicExpression::or_expr(left, right);
                } else if (pos + 3 <= expression.size() && expression.substr(pos, 3) == "XOR") {
                    pos += 3;
                    auto right = parse_and();
                    // XOR is equivalent to (A AND NOT B) OR (NOT A AND B)
                    auto not_left = LogicExpression::not_expr(left);
                    auto not_right = LogicExpression::not_expr(right);
                    auto left_and_not_right = LogicExpression::and_expr(left, not_right);
                    auto not_left_and_right = LogicExpression::and_expr(not_left, right);
                    left = LogicExpression::or_expr(left_and_not_right, not_left_and_right);
                } else {
                    break;
                }
            }
            
            return left;
        }
        
        // Parse IMPLIES expressions
        std::shared_ptr<LogicExpression> parse_implies() {
            auto left = parse_or();
            
            skip_whitespace();
            
            if (pos + 7 <= expression.size() && expression.substr(pos, 7) == "IMPLIES") {
                pos += 7;
                auto right = parse_implies();  // Right-associative
                return LogicExpression::implies_expr(left, right);
            }
            
            return left;
        }
        
        // Parse EQUIVALENT expressions
        std::shared_ptr<LogicExpression> parse_equivalence() {
            auto left = parse_implies();
            
            skip_whitespace();
            
            if (pos + 10 <= expression.size() && expression.substr(pos, 10) == "EQUIVALENT") {
                pos += 10;
                auto right = parse_equivalence();  // Right-associative
                return LogicExpression::equivalent_expr(left, right);
            }
            
            return left;
        }
    };
    
    // Parse a logic expression from a string
    std::shared_ptr<LogicExpression> parse_expression(const std::string& expr_str) {
        LogicParser parser(expr_str);
        return parser.parse();
    }
}

/**
 * @brief Logic operations plugin for Woflang
 * 
 * This plugin provides boolean logic operations and propositional logic tools.
 */
class LogicOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // ----- Boolean Operations -----
        
        // and: Logical AND
        interp.register_op("and", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("and requires two values");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Convert to boolean
            bool bool_a = false;
            bool bool_b = false;
            
            if (a.type == WofType::Integer) {
                bool_a = std::get<int64_t>(a.value) != 0;
            } else if (a.type == WofType::Double) {
                bool_a = std::get<double>(a.value) != 0.0;
            } else {
                throw std::runtime_error("and requires numeric values");
            }
            
            if (b.type == WofType::Integer) {
                bool_b = std::get<int64_t>(b.value) != 0;
            } else if (b.type == WofType::Double) {
                bool_b = std::get<double>(b.value) != 0.0;
            } else {
                throw std::runtime_error("and requires numeric values");
            }
            
            // Perform the operation
            bool result = logic_helpers::boolean_and(bool_a, bool_b);
            
            // Push the result
            interp.stack.emplace_back(result ? 1LL : 0LL);
        });
        
        // or: Logical OR
        interp.register_op("or", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("or requires two values");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Convert to boolean
            bool bool_a = false;
            bool bool_b = false;
            
            if (a.type == WofType::Integer) {
                bool_a = std::get<int64_t>(a.value) != 0;
            } else if (a.type == WofType::Double) {
                bool_a = std::get<double>(a.value) != 0.0;
            } else {
                throw std::runtime_error("or requires numeric values");
            }
            
            if (b.type == WofType::Integer) {
                bool_b = std::get<int64_t>(b.value) != 0;
            } else if (b.type == WofType::Double) {
                bool_b = std::get<double>(b.value) != 0.0;
            } else {
                throw std::runtime_error("or requires numeric values");
            }
            
            // Perform the operation
            bool result = logic_helpers::boolean_or(bool_a, bool_b);
            
            // Push the result
            interp.stack.emplace_back(result ? 1LL : 0LL);
        });
        
        // xor: Logical XOR
        interp.register_op("xor", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("xor requires two values");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Convert to boolean
            bool bool_a = false;
            bool bool_b = false;
            
            if (a.type == WofType::Integer) {
                bool_a = std::get<int64_t>(a.value) != 0;
            } else if (a.type == WofType::Double) {
                bool_a = std::get<double>(a.value) != 0.0;
            } else {
                throw std::runtime_error("xor requires numeric values");
            }
            
            if (b.type == WofType::Integer) {
                bool_b = std::get<int64_t>(b.value) != 0;
            } else if (b.type == WofType::Double) {
                bool_b = std::get<double>(b.value) != 0.0;
            } else {
                throw std::runtime_error("xor requires numeric values");
            }
            
            // Perform the operation
            bool result = logic_helpers::boolean_xor(bool_a, bool_b);
            
            // Push the result
            interp.stack.emplace_back(result ? 1LL : 0LL);
        });
        
        // not: Logical NOT
        interp.register_op("not", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("not requires a value");
            }
            
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Convert to boolean
            bool bool_a = false;
            
            if (a.type == WofType::Integer) {
                bool_a = std::get<int64_t>(a.value) != 0;
            } else if (a.type == WofType::Double) {
                bool_a = std::get<double>(a.value) != 0.0;
            } else {
                throw std::runtime_error("not requires a numeric value");
            }
            
            // Perform the operation
            bool result = logic_helpers::boolean_not(bool_a);
            
            // Push the result
            interp.stack.emplace_back(result ? 1LL : 0LL);
        });
        
        // implies: Logical implication
        interp.register_op("implies", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("implies requires two values");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Convert to boolean
            bool bool_a = false;
            bool bool_b = false;
            
            if (a.type == WofType::Integer) {
                bool_a = std::get<int64_t>(a.value) != 0;
            } else if (a.type == WofType::Double) {
                bool_a = std::get<double>(a.value) != 0.0;
            } else {
                throw std::runtime_error("implies requires numeric values");
            }
            
            if (b.type == WofType::Integer) {
                bool_b = std::get<int64_t>(b.value) != 0;
            } else if (b.type == WofType::Double) {
                bool_b = std::get<double>(b.value) != 0.0;
            } else {
                throw std::runtime_error("implies requires numeric values");
            }
            
            // Perform the operation
            bool result = logic_helpers::boolean_implies(bool_a, bool_b);
            
            // Push the result
            interp.stack.emplace_back(result ? 1LL : 0LL);
        });
        
        // equivalent: Logical equivalence
        interp.register_op("equivalent", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("equivalent requires two values");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Convert to boolean
            bool bool_a = false;
            bool bool_b = false;
            
            if (a.type == WofType::Integer) {
                bool_a = std::get<int64_t>(a.value) != 0;
            } else if (a.type == WofType::Double) {
                bool_a = std::get<double>(a.value) != 0.0;
            } else {
                throw std::runtime_error("equivalent requires numeric values");
            }
            
            if (b.type == WofType::Integer) {
                bool_b = std::get<int64_t>(b.value) != 0;
            } else if (b.type == WofType::Double) {
                bool_b = std::get<double>(b.value) != 0.0;
            } else {
                throw std::runtime_error("equivalent requires numeric values");
            }
            
            // Perform the operation
            bool result = logic_helpers::boolean_equivalent(bool_a, bool_b);
            
            // Push the result
            interp.stack.emplace_back(result ? 1LL : 0LL);
        });
        
        // nand: Logical NAND
        interp.register_op("nand", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("nand requires two values");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Convert to boolean
            bool bool_a = false;
            bool bool_b = false;
            
            if (a.type == WofType::Integer) {
                bool_a = std::get<int64_t>(a.value) != 0;
            } else if (a.type == WofType::Double) {
                bool_a = std::get<double>(a.value) != 0.0;
            } else {
                throw std::runtime_error("nand requires numeric values");
            }
            
            if (b.type == WofType::Integer) {
                bool_b = std::get<int64_t>(b.value) != 0;
            } else if (b.type == WofType::Double) {
                bool_b = std::get<double>(b.value) != 0.0;
            } else {
                throw std::runtime_error("nand requires numeric values");
            }
            
            // Perform the operation
            bool result = logic_helpers::boolean_nand(bool_a, bool_b);
            
            // Push the result
            interp.stack.emplace_back(result ? 1LL : 0LL);
        });
        
        // nor: Logical NOR
        interp.register_op("nor", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("nor requires two values");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Convert to boolean
            bool bool_a = false;
            bool bool_b = false;
            
            if (a.type == WofType::Integer) {
                bool_a = std::get<int64_t>(a.value) != 0;
            } else if (a.type == WofType::Double) {
                bool_a = std::get<double>(a.value) != 0.0;
            } else {
                throw std::runtime_error("nor requires numeric values");
            }
            
            if (b.type == WofType::Integer) {
                bool_b = std::get<int64_t>(b.value) != 0;
            } else if (b.type == WofType::Double) {
                bool_b = std::get<double>(b.value) != 0.0;
            } else {
                throw std::runtime_error("nor requires numeric values");
            }
            
            // Perform the operation
            bool result = logic_helpers::boolean_nor(bool_a, bool_b);
            
            // Push the result
            interp.stack.emplace_back(result ? 1LL : 0LL);
        });
        
        // ----- Truth Tables -----
        
        // truth_table_and: Display truth table for AND
        interp.register_op("truth_table_and", [](WoflangInterpreter& interp) {
            std::string table = logic_helpers::generate_truth_table("AND", logic_helpers::boolean_and);
            std::cout << table;
        });
        
        // truth_table_or: Display truth table for OR
        interp.register_op("truth_table_or", [](WoflangInterpreter& interp) {
            std::string table = logic_helpers::generate_truth_table("OR", logic_helpers::boolean_or);
            std::cout << table;
        });
        
        // truth_table_xor: Display truth table for XOR
        interp.register_op("truth_table_xor", [](WoflangInterpreter& interp) {
            std::string table = logic_helpers::generate_truth_table("XOR", logic_helpers::boolean_xor);
            std::cout << table;
        });
        
        // truth_table_not: Display truth table for NOT
        interp.register_op("truth_table_not", [](WoflangInterpreter& interp) {
            std::string table = logic_helpers::generate_unary_truth_table("NOT", logic_helpers::boolean_not);
            std::cout << table;
        });
        
        // truth_table_implies: Display truth table for IMPLIES
        interp.register_op("truth_table_implies", [](WoflangInterpreter& interp) {
            std::string table = logic_helpers::generate_truth_table("IMPLIES", logic_helpers::boolean_implies);
            std::cout << table;
        });
        
        // truth_table_equivalent: Display truth table for EQUIVALENT
        interp.register_op("truth_table_equivalent", [](WoflangInterpreter& interp) {
            std::string table = logic_helpers::generate_truth_table("EQUIV", logic_helpers::boolean_equivalent);
            std::cout << table;
        });
        
        // truth_table_nand: Display truth table for NAND
        interp.register_op("truth_table_nand", [](WoflangInterpreter& interp) {
            std::string table = logic_helpers::generate_truth_table("NAND", logic_helpers::boolean_nand);
            std::cout << table;
        });
        
        // truth_table_nor: Display truth table for NOR
        interp.register_op("truth_table_nor", [](WoflangInterpreter& interp) {
            std::string table = logic_helpers::generate_truth_table("NOR", logic_helpers::boolean_nor);
            std::cout << table;
        });
        
        // ----- Propositional Logic Operations -----
        
        // logic_eval: Evaluate a logical expression
        interp.register_op("logic_eval", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("logic_eval requires an expression");
            }
            
            auto expr_val = interp.stack.back(); interp.stack.pop_back();
            
            if (expr_val.type != WofType::String && expr_val.type != WofType::Symbol) {
                throw std::runtime_error("Expression must be a string or symbol");
            }
            
            std::string expr_str = std::get<std::string>(expr_val.value);
            
            try {
                // Parse the expression
                auto expr = logic_helpers::parse_expression(expr_str);
                
                // Get the variables used in the expression
                std::set<std::string> vars = expr->get_variables();
                
                // Check if we have assignments for all variables
                if (!vars.empty() && interp.stack.size() < 2 * vars.size()) {
                    throw std::runtime_error("Missing variable assignments");
                }
                
                // Get the variable assignments
                std::map<std::string, bool> assignments;
                
                if (!vars.empty()) {
                    for (size_t i = 0; i < vars.size(); i++) {
                        if (interp.stack.size() < 2) {
                            throw std::runtime_error("Missing variable assignments");
                        }
                        
                        auto value = interp.stack.back(); interp.stack.pop_back();
                        auto name = interp.stack.back(); interp.stack.pop_back();
                        
                        if (name.type != WofType::String && name.type != WofType::Symbol) {
                            throw std::runtime_error("Variable name must be a string or symbol");
                        }
                        
                        bool bool_value = false;
                        if (value.type == WofType::Integer) {
                            bool_value = std::get<int64_t>(value.value) != 0;
                        } else if (value.type == WofType::Double) {
                            bool_value = std::get<double>(value.value) != 0.0;
                        } else {
                            throw std::runtime_error("Variable value must be numeric");
                        }
                        
                        assignments[std::get<std::string>(name.value)] = bool_value;
                    }
                }
                
                // Evaluate the expression
                bool result = expr->evaluate(assignments);
                
                // Print the evaluation
                std::cout << "Expression: " << expr->to_string() << "\n";
                
                if (!assignments.empty()) {
                    std::cout << "Assignments:\n";
                    for (const auto& [var, val] : assignments) {
                        std::cout << "  " << var << " = " << (val ? "true" : "false") << "\n";
                    }
                }
                
                std::cout << "Result: " << (result ? "true" : "false") << "\n";
                
                // Push the result
                interp.stack.emplace_back(result ? 1LL : 0LL);
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("logic_eval error: ") + e.what());
            }
        });
        
        // logic_truth_table: Generate a truth table for a logical expression
        interp.register_op("logic_truth_table", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("logic_truth_table requires an expression");
            }
            
            auto expr_val = interp.stack.back(); interp.stack.pop_back();
            
            if (expr_val.type != WofType::String && expr_val.type != WofType::Symbol) {
                throw std::runtime_error("Expression must be a string or symbol");
            }
            
            std::string expr_str = std::get<std::string>(expr_val.value);
            
            try {
                // Parse the expression
                auto expr = logic_helpers::parse_expression(expr_str);
                
                // Generate the truth table
                std::string table = expr->truth_table();
                
                // Print the truth table
                std::cout << table;
                
                // Push the expression string back onto the stack
                interp.stack.push_back(expr_val);
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("logic_truth_table error: ") + e.what());
            }
        });
        
        // ----- Educational Operations -----
        
        // logic_gates: Display information about logic gates
        interp.register_op("logic_gates", [](WoflangInterpreter& interp) {
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
        interp.register_op("logic_tutorial", [](WoflangInterpreter& interp) {
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
            std::cout << "Use 'logic_eval' to evaluate logical expressions.\n";
            std::cout << "Use 'logic_truth_table' to generate truth tables for expressions.\n";
        });
    }
};

} // namespace woflang

// Plugin registration function
WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::LogicOpsPlugin plugin;
    plugin.register_ops(interp);
}
