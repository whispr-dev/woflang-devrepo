// wof_markov_math_suggestions.hpp
// Simple Markov-like pairs for WOFLANG math autocomplete

#pragma once
#include <vector>
#include <string>
#include <unordered_map>

using MarkovTable = std::unordered_map<std::string, std::vector<std::string>>;

inline MarkovTable buildMarkovSuggestionTable() {
    return {
        { "diff",   { "X", "X^2", "sin(X)", "cos(X)", "(X + 1)" }},
        { "∫",      { "X dX", "X^2 dX", "sin(X) dX", "1/X dX" }},
        { "X + X",  { "2 * X" }},
        { "X * 1",  { "X" }},
        { "X * X",  { "X^2" }},
        { "X + 1",  { "(X + 1)^2" }},
        { "(X + 1)^2", { "X^2 + 2*X + 1" }},
        { "log(X^2)", { "2 * log(X)" }},
        { "ln(e^X)",  { "X" }},
        { "sin^2(X) + cos^2(X)", { "1" }}
    };
}
