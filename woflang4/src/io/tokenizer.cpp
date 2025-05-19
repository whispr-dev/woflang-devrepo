#include "../core/WofType.hpp"
#include "../core/WofToken.hpp"
#include "../../src/core/woflang.hpp"
#include "../simd/simd_utf32.hpp"
#include <regex>
#include <sstream>
#include <locale>
#include <cctype>
#include <algorithm>

namespace woflang {

/**
 * @brief Tokenize a line of Woflang code
 * 
 * This function splits a line of code into tokens, handling
 * quoted strings, symbols, and whitespace properly.
 * 
 * @param line Input line of code
 * @return Vector of tokens
 */
std::vector<std::string> WoflangInterpreter::tokenize(const std::string& line) {
    // Skip empty lines or comments
    if (line.empty() || line[0] == '#') {
        return {};
    }
    
    std::vector<std::string> tokens;
    std::string token;
    bool in_string = false;
    bool escaped = false;
    
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        
        // Handle string literals
        if (c == '"' && !escaped) {
            in_string = !in_string;
            token += c;
            
            // If we just closed a string, add it to tokens
            if (!in_string) {
                tokens.push_back(token);
                token.clear();
            }
            continue;
        }
        
        // Handle escape sequences
        if (c == '\\' && !escaped) {
            escaped = true;
            continue;
        }
        
        // Process escaped character
        if (escaped) {
            switch (c) {
                case 'n': token += '\n'; break;
                case 't': token += '\t'; break;
                case 'r': token += '\r'; break;
                case '\\': token += '\\'; break;
                case '"': token += '"'; break;
                default: token += c; break;
            }
            escaped = false;
            continue;
        }
        
        // Inside a string, just add the character
        if (in_string) {
            token += c;
            continue;
        }
        
        // Whitespace terminates a token
        if (std::isspace(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            continue;
        }
        
        // Special token terminators
        if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') {
            // Add current token if not empty
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            
            // Add special character as its own token
            tokens.push_back(std::string(1, c));
            continue;
        }
        
        // Append character to current token
        token += c;
    }
    
    // Add final token if not empty
    if (!token.empty()) {
        tokens.push_back(token);
    }
    
    // Check for unclosed strings
    if (in_string) {
        throw std::runtime_error("Unclosed string literal");
    }
    
    return tokens;
}

/**
 * @brief Dispatch a token to the appropriate handler
 * 
 * This function determines what to do with a token - execute
 * an operation, push a value, etc.
 * 
 * @param token Input token
 */
void WoflangInterpreter::dispatch_token(const std::string& token) {
    // First, check if it's an operation
    auto it = op_handlers.find(token);
    if (it != op_handlers.end()) {
        // It's an operation, execute it
        try {
            it->second(*this);
        } catch (const std::exception& e) {
            error("Error executing operation '" + token + "': " + e.what());
        }
        return;
    }
    
    // Try to parse as a number
    try {
        // Check if it's an integer
        size_t pos = 0;
        int64_t int_val = std::stoll(token, &pos);
        if (pos == token.size()) {
            // Successfully parsed as integer
            stack.emplace_back(int_val);
            return;
        }
        
        // Check if it's a double
        double double_val = std::stod(token, &pos);
        if (pos == token.size()) {
            // Successfully parsed as double
            stack.emplace_back(double_val);
            return;
        }
    } catch (const std::exception&) {
        // Not a number, continue
    }
    
    // If it's a quoted string, parse it as a string
    if (token.size() >= 2 && token.front() == '"' && token.back() == '"') {
        // Remove the quotes and handle escape sequences
        std::string content = token.substr(1, token.size() - 2);
        std::string unescaped;
        
        for (size_t i = 0; i < content.size(); ++i) {
            if (content[i] == '\\' && i + 1 < content.size()) {
                // Handle escape sequence
                switch (content[i + 1]) {
                    case 'n': unescaped += '\n'; break;
                    case 't': unescaped += '\t'; break;
                    case 'r': unescaped += '\r'; break;
                    case '\\': unescaped += '\\'; break;
                    case '"': unescaped += '"'; break;
                    default: unescaped += content[i + 1]; break;
                }
                ++i; // Skip the escaped character
            } else {
                unescaped += content[i];
            }
        }
        
        stack.emplace_back(unescaped);
        return;
    }
    
    // Otherwise, it's a symbol
    stack.emplace_back(token, WofType::Symbol);
}

} // namespace woflang