// repl_suggest_accept_buffer.cpp
// Enhanced :suggest ++ that stores accepted suggestion in history

#include "wof_markov_math_suggestions.hpp"
#include <iostream>
#include <string>
#include <vector>

std::string apply_and_store_suggestion(const std::string& expr, std::vector<std::string>& history) {
    auto table = buildMarkovSuggestionTable();

    for (auto& [key, options] : table) {
        if (expr.find(key) != std::string::npos && !options.empty()) {
            std::string alt = options.front();
            std::string result = expr;
            result.replace(result.find(key), key.length(), alt);
            std::cout << "[suggest:++] " << expr << " → " << result << "\n";
            history.push_back(result);
            return result;
        }
    }

    std::cout << "[suggest:++] No suggestion matched for: " << expr << "\n";
    return expr;
}
