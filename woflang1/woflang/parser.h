// parser.h
#include "woflang_config.h"
#include "constants.h"
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "error_system.h"

namespace woflang {

// Get system instances
auto& cmdSystem = woflang::CommandSystem::getInstance();
auto& dict = woflang::CommandDictionary::getInstance();
auto& errorSystem = woflang::ErrorSystem::getInstance();

// Print version info
std::cout << "WoflangCPP v" 
          << woflang::VERSION.major << "."
          << woflang::VERSION.minor << "."
          << woflang::VERSION.patch << std::endl;

// Load default dictionary if no file provided
std::string dictFile = (argc > 1) ? argv[1] : woflang::constants::DEFAULT_DICTIONARY_FILE;

// Forward declarations
class CommandDictionary;
class CommandSystem;

// Token types
enum class TokenType {
    Number,
    Operator,
    LeftParen,
    RightParen,
    Variable,
    EndOfLine
};

// Token structure
struct Token {
    TokenType type;
    std::string value;
    int position;  // Position in input for error reporting
    
    Token(TokenType t, std::string v, int pos) 
    struct TokenPosition {
        size_t line;
        size_t column;
        size_t absolute;
    };
        : type(t), value(std::move(v)), position(pos) {}
};

// Abstract syntax tree node
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual double evaluate() = 0;
};

// Number node
class NumberNode : public ASTNode {
    double value;
public:
    explicit NumberNode(double v) : value(v) {}
    double evaluate() override { return value; }
};

// Operator node
class OperatorNode : public ASTNode {
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
public:
    OperatorNode(std::string op, std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
        : op(std::move(op)), left(std::move(l)), right(std::move(r)) {}
    double evaluate() override;
};

class Parser {
public:
    Parser(CommandSystem& cmdSys, CommandDictionary& dict);
    
    // Parse input string and return AST
    std::unique_ptr<ASTNode> parse(const std::string& input);
    
    // Get any error that occurred during parsing
    std::string getLastError() const { return lastError; }

private:
    CommandSystem& cmdSystem;
    CommandDictionary& dictionary;
    std::vector<Token> tokens;
    size_t currentToken;
    std::string lastError;
    
    // Lexer functions
    std::vector<Token> tokenize(const std::string& input);
    bool isOperator(const std::string& str) const;
    bool isNumber(const std::string& str) const;
    
    // Parser functions
    std::unique_ptr<ASTNode> parseExpression();
    std::unique_ptr<ASTNode> parseTerm();
    std::unique_ptr<ASTNode> parseFactor();
    
    // Helper functions
    Token& getCurrentToken();
    void advance();
    bool match(TokenType type);
    void setError(const std::string& error);
};

} // namespace woflang