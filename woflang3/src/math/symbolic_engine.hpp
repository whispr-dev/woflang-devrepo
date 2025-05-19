#pragma once
#include "../core/woflang.hpp"
#include <regex>
#include <iostream>

// Add basic pattern-matching/simplification and unit support
inline void register_symbolic_ops(WoflangInterpreter& interp) {
    // Symbolic simplification: X + X => 2*X
    interp.register_op("simplify", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 3) return;
        auto c = interp.stack.back(); interp.stack.pop_back();
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        // Only: a + a
        if (a.type == WofType::Symbol && b.type == WofType::Symbol && std::get<std::string>(a.value) == std::get<std::string>(b.value) && c.type == WofType::String && std::get<std::string>(c.value) == "+") {
            interp.stack.emplace_back(2);
            interp.stack.push_back(a); // X
            interp.stack.emplace_back("*", WofType::String);
        } else {
            interp.stack.push_back(a);
            interp.stack.push_back(b);
            interp.stack.push_back(c);
        }
    });

    // Units: assign a unit to a value
    interp.register_op("unit", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) return;
        auto unit = interp.stack.back(); interp.stack.pop_back();
        auto val = interp.stack.back(); interp.stack.pop_back();
        if ((val.type == WofType::Integer || val.type == WofType::Double) && unit.type == WofType::Symbol) {
            std::string u = std::get<std::string>(unit.value);
            if (val.type == WofType::Integer)
                interp.stack.emplace_back(std::get<int64_t>(val.value), u);
            else
                interp.stack.emplace_back(std::get<double>(val.value), u);
        } else {
            interp.stack.push_back(val);
            interp.stack.push_back(unit);
        }
    });

    // Multiply units: e.g. 2 m * 3 m => 6 m^2
    interp.register_op("mul_unit", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) return;
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();
        if (a.unit && b.unit && *a.unit == *b.unit) {
            if (a.type == WofType::Integer && b.type == WofType::Integer)
                interp.stack.emplace_back(std::get<int64_t>(a.value) * std::get<int64_t>(b.value), *a.unit + "^2");
            else if (a.type == WofType::Double && b.type == WofType::Double)
                interp.stack.emplace_back(std::get<double>(a.value) * std::get<double>(b.value), *a.unit + "^2");
        } else {
            interp.stack.push_back(a);
            interp.stack.push_back(b);
        }
    });

    // ...add more: conversions, pattern-matching, etc.
}
