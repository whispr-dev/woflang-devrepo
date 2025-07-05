#include "tokenizer.hpp"
#include <sstream>
#include <cctype>

namespace woflang {

std::vector<std::string> tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(input);
    char c;
    
    while (iss.get(c)) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            // Whitespace - end current token
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } 
        else if (c == '(' || c == ')' || c == '[' || c == ']' || 
                 c == '{' || c == '}' || c == ',' || c == ';') {
            // Only treat specific punctuation as separators
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.emplace_back(1, c);
        }
        else {
            // Everything else (including underscores, Unicode, etc.) goes into tokens
            token += c;
        }
    }
    
    if (!token.empty()) {
        tokens.push_back(token);
    }
    
    return tokens;
}

}