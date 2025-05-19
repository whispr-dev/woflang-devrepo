#include "../../src/core/woflang.hpp"
#include <iostream>
#include <regex>

// Symbolic solve for basic equations (e.g., "2 X = 4")
class SymbolicSolvePlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("solve", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 4) return;
            auto rhs = interp.stack.back(); interp.stack.pop_back();     // e.g., 4
            auto eq = interp.stack.back(); interp.stack.pop_back();      // e.g., "="
            auto var = interp.stack.back(); interp.stack.pop_back();     // e.g., "X"
            auto coeff = interp.stack.back(); interp.stack.pop_back();   // e.g., 2

            if (coeff.type == WofType::Integer && eq.type == WofType::Symbol && eq.value.type == WofType::String ? std::get<std::string>(eq.value.value) : "" == "=") {
                int64_t c = std::get<int64_t>(coeff.value);
                if (var.type == WofType::Symbol && rhs.type ==
