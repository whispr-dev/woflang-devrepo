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
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else if (std::ispunct(static_cast<unsigned char>(c))) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.emplace_back(1, c);
        } else {
            token += c;
        }
    }
    if (!token.empty())
        tokens.push_back(token);
    return tokens;
}

}
