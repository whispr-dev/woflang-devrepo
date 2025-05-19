// repl_suggest_trigger_patch.cpp
// Adds inline trigger '...' for math suggestion

#include "wof_markov_math_suggestions.hpp"
#include <iostream>
#include <string>

void check_suggestion_trigger(const std::string& line) {
    if (!line.ends_with("...")) return;

    auto table = buildMarkovSuggestionTable();
    std::string expr = line.substr(0, line.size() - 3); // remove "..."

    for (auto& [key, options] : table) {
        if (expr.find(key) != std::string::npos) {
            std::cout << "[auto-suggest] Based on "" << key << "":\n";
            for (const auto& alt : options) {
                std::cout << " → " << expr << " → " << alt << "\n";
            }
            return;
        }
    }

    std::cout << "[auto-suggest] No suggestions for: " << expr << "\n";
}
