#ifndef WOF_MARKOV_MATH_SUGGESTIONS_HPP
#define WOF_MARKOV_MATH_SUGGESTIONS_HPP

#include <string>
#include <map>

class MarkovMathSuggester {
public:
    void suggest(const std::string& input) {
        // Stub: Print suggestion (replace with real logic)
        std::cout << "Suggestion for " << input << ": [stub]\n";
    }

    void buildMarkovSuggestionTable() {
        // Stub: Populate suggestions (replace with real logic)
        suggestions["sin"] = {"cos", "tan"};
        suggestions["cos"] = {"sin", "tan"};
    }

    const std::map<std::string, std::vector<std::string>>& getSuggestions() const {
        return suggestions;
    }

private:
    std::map<std::string, std::vector<std::string>> suggestions;
};

#endif // WOF_MARKOV_MATH_SUGGESTIONS_HPP