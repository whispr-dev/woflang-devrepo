// repl_suggest_accept.cpp
// Implements :suggest ++ to auto-accept first matching suggestion

#include "wof_markov_math_suggestions.hpp"
#include <iostream>
#include <string>

std::string apply_first_suggestion(const std::string& expr) {
    auto table = buildMarkovSuggestionTable();

    for (auto& [key, options] : table) {
        if (expr.find(key) != std::string::npos && !options.empty()) {
            std::string alt = options.front();
            std::string result = expr;
            result.replace(result.find(key), key.length(), alt);
            std::cout << "[suggest:++] " << expr << " → " << result << "\n";
            return result;
        }
    }

    std::cout << "[suggest:++] No suggestion matched for: " << expr << "\n";
    return expr;
}
