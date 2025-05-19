// parser.cpp
#include "woflang_config.h"
#include "constants.h"
#include "parser.h"
#include "command_dictionary.h"
#include "command_system.h"
#include <sstream>
#include <cctype>
#include <stack>

namespace woflang {

    class ParserState {
        std::vector<std::string> errors;
        bool recoveryMode = false;
        
        void synchronize() {
            // Skip tokens until finding a safe point to resume parsing
            while (currentToken < tokens.size()) {
                if (isStatementBoundary()) break;
                advance();
            }
        }
    };

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

Parser::Parser(CommandSystem& cmdSys, CommandDictionary& dict)
    : cmdSystem(cmdSys), dictionary(dict), currentToken(0) {}


std::vector<Token> Parser::tokenize(const std::string& input) {
    // Trim whitespace from input
    std::string cleanInput = Utils::trim(input);
        
    // Split into initial tokens
    std::vector<std::string> rawTokens = Utils::split(cleanInput, ' ');
    // Rest of tokenize code...
}    

    std::vector<Token> tokens;
    std::string current;
    int position = 0;

    auto flushCurrent = [&]() {
        if (!current.empty()) {
            if (isNumber(current)) {
                tokens.emplace_back(TokenType::Number, current, position - current.length());
            } else if (dictionary.hasSymbol(current)) {
                tokens.emplace_back(TokenType::Operator, current, position - current.length());
            }
            current.clear();
        }
    };

    while (position < input.length()) {
        char c = input[position];
        
        // Handle whitespace
        if (std::isspace(c)) {
            flushCurrent();
            position++;
            continue;
        }

        // Handle parentheses
        if (c == '(') {
            flushCurrent();
            tokens.emplace_back(TokenType::LeftParen, "(", position);
            position++;
            continue;
        }
        if (c == ')') {
            flushCurrent();
            tokens.emplace_back(TokenType::RightParen, ")", position);
            position++;
            continue;
        }

        // Handle numbers
        if (std::isdigit(c) || c == '.') {
            if (!current.empty() && !isNumber(current)) {
                flushCurrent();
            }
            current += c;
            position++;
            continue;
        }

        // Handle UTF-8 characters
        int charLength = 1;
        if ((c & 0xE0) == 0xC0) charLength = 2;  // 2-byte UTF-8
        else if ((c & 0xF0) == 0xE0) charLength = 3;  // 3-byte UTF-8
        else if ((c & 0xF8) == 0xF0) charLength = 4;  // 4-byte UTF-8

        if (charLength > 1) {
            flushCurrent();
            if (position + charLength <= input.length()) {
                std::string utf8char = input.substr(position, charLength);
                if (dictionary.hasSymbol(utf8char)) {
                    tokens.emplace_back(TokenType::Operator, utf8char, position);
                } else {
                    setError("Unknown operator at position " + std::to_string(position));
                    return {};
                }
            }
            position += charLength;
            continue;
        }

        // Handle other characters
        current += c;
        position++;
    }

    flushCurrent();
    tokens.emplace_back(TokenType::EndOfLine, "", position);
    return tokens;
}

std::unique_ptr<ASTNode> Parser::parse(const std::string& input) {
    tokens = tokenize(input);
    if (tokens.empty()) {
        return nullptr;
    }
    currentToken = 0;
    return parseExpression();
}

std::unique_ptr<ASTNode> Parser::parseExpression() {
    auto left = parseTerm();
    if (!left) return nullptr;

    while (currentToken < tokens.size() && 
           tokens[currentToken].type == TokenType::Operator) {
        std::string op = tokens[currentToken].value;
        advance();
        
        auto right = parseTerm();
        if (!right) return nullptr;

        left = std::make_unique<OperatorNode>(op, std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::parseTerm() {
    auto left = parseFactor();
    if (!left) return nullptr;

    while (currentToken < tokens.size() && 
           tokens[currentToken].type == TokenType::Operator) {
        std::string op = tokens[currentToken].value;
        // Check if operator has higher precedence
        if (op != "⊗" && op != "⊘") break;  // Example for multiplication and division
        
        advance();
        auto right = parseFactor();
        if (!right) return nullptr;

        left = std::make_unique<OperatorNode>(op, std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<ASTNode> Parser::parseFactor() {
    if (match(TokenType::Number)) {
        double value = std::stod(tokens[currentToken - 1].value);
        return std::make_unique<NumberNode>(value);
    }

    if (match(TokenType::LeftParen)) {
        auto node = parseExpression();
        if (!match(TokenType::RightParen)) {
            setError("Expected closing parenthesis");
            return nullptr;
        }
        return node;
    }

    setError("Unexpected token at position " + 
             std::to_string(tokens[currentToken].position));
    return nullptr;
}

double OperatorNode::evaluate() {
    double leftVal = left->evaluate();
    double rightVal = right->evaluate();
    
    // Create operands array for command system
    double operands[] = {leftVal, rightVal};
    
    // Execute command through command system
    // Note: This would need access to CommandSystem instance
    // You might want to make this a static member or pass it in
    auto& cmdSystem = CommandSystem::getInstance();
    cmdSystem.executeCommand(op, operands, 2);
    
    return operands[0];  // Return result
}

Token& Parser::getCurrentToken() {
    return tokens[currentToken];
}

void Parser::advance() {
    if (currentToken < tokens.size()) {
        currentToken++;
    }
}

bool Parser::match(TokenType type) {
    if (currentToken < tokens.size() && tokens[currentToken].type == type) {
        currentToken++;
        return true;
    }
    return false;
}

bool Parser::isOperator(const std::string& str) const {
    return dictionary.hasSymbol(str);
}

bool Parser::isNumber(const std::string& str) const {
    if (str.empty()) return false;
    
    bool hasDecimal = false;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '.') {
            if (hasDecimal) return false;
            hasDecimal = true;
        } else if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

void Parser::setError(const std::string& error) {
    lastError = error;
}

} // namespace woflang