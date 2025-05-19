// repl_suggest_command.cpp
// Implements :suggest — expands math expressions using Markov-style completion

#include "wof_markov_math_suggestions.hpp"
#include <iostream>
#include <string>

void handle_suggest_command(const std::string& input) {
    auto table = buildMarkovSuggestionTable();
    std::string expr = input.substr(8); // strip ":suggest"

    for (auto& [key, options] : table) {
        if (expr.find(key) != std::string::npos) {
            std::cout << "[suggest] completions for "" << key << "":\n";
            for (const auto& alt : options) {
                std::cout << " → " << expr << " → " << alt << "\n";
            }
            return;
        }
    }

    std::cout << "[suggest] no suggestions found for: " << expr << "\n";
}
