#include "wof_markov_math_suggestions.hpp"
#include <iostream>
#include <string>
#include <vector>

void handle_suggest_command(const std::string& input) {
    MarkovMathSuggester suggester;
    suggester.buildMarkovSuggestionTable();

    const auto& suggestions = suggester.getSuggestions();
    for (const auto& [key, options] : suggestions) {
        std::cout << "Key: " << key << "\n";
        for (const auto& alt : options) {
            std::cout << "  Option: " << alt << "\n";
        }
    }

    // Call suggest for the input
    suggester.suggest(input);
}