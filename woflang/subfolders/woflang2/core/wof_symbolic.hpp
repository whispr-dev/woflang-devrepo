// wof_symbolic.hpp
// Defines symbolic structure for expression manipulation

#pragma once
#include <string>
#include <variant>
#include <vector>
#include <iostream>

struct WofSymbol;

using WofSymbolValue = std::variant<
    int64_t,              // literal value
    std::string,          // variable name (e.g. "x")
    std::vector<WofSymbol> // expression tree: [lhs, op, rhs]
>;

struct WofSymbol {
    WofSymbolValue value;

    void print() const {
        if (std::holds_alternative<int64_t>(value)) {
            std::cout << std::get<int64_t>(value);
        } else if (std::holds_alternative<std::string>(value)) {
            std::cout << std::get<std::string>(value);
        } else if (std::holds_alternative<std::vector<WofSymbol>>(value)) {
            const auto& list = std::get<std::vector<WofSymbol>>(value);
            std::cout << "[ ";
            for (const auto& e : list) {
                e.print();
                std::cout << " ";
            }
            std::cout << "]";
        }
    }
};
