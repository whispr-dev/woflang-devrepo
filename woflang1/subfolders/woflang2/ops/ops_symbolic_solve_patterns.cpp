// ops_symbolic_solve_patterns.cpp
// Expands solve() to handle X + A = B and A * X + B = C

#include "wof_interpreter.hpp"
#include "wof_symbolic.hpp"
#include <iostream>
#include <string>
#include <vector>

void register_symbolic_solve_patterns(WofInterpreter& vm) {
    vm.registerOpcode(3202, [](WofInterpreter& vm, const WofToken&) {
        std::cout << "[solve] attempting extended solve...\n";
        auto eq = vm.popSymbol();

        if (!std::holds_alternative<std::vector<WofSymbol>>(eq.value)) {
            std::cout << "[solve] not a symbolic expression.\n";
            return;
        }

        const auto& tree = std::get<std::vector<WofSymbol>>(eq.value);
        if (tree.size() != 3 || !std::holds_alternative<std::string>(tree[1].value) || std::get<std::string>(tree[1].value) != "=") {
            std::cout << "[solve] expected A = B form\n";
            return;
        }

        const auto& lhs = tree[0];
        const auto& rhs = tree[2];

        // Pattern: [X + A] = B → X = B - A
        if (std::holds_alternative<std::vector<WofSymbol>>(lhs.value)) {
            const auto& addform = std::get<std::vector<WofSymbol>>(lhs.value);
            if (addform.size() == 3 &&
                std::holds_alternative<std::string>(addform[0].value) &&
                std::get<std::string>(addform[0].value) == "X" &&
                std::holds_alternative<std::string>(addform[1].value) &&
                std::get<std::string>(addform[1].value) == "+" &&
                std::holds_alternative<int64_t>(addform[2].value) &&
                std::holds_alternative<int64_t>(rhs.value)) {

                int64_t A = std::get<int64_t>(addform[2].value);
                int64_t B = std::get<int64_t>(rhs.value);
                int64_t X = B - A;

                std::cout << "[solve] X = " << B << " - " << A << " = " << X << "\n";
                vm.pushValue(WofValue(X));
                return;
            }
        }

        // Pattern: [A * X + B] = C → X = (C - B) / A
        if (std::holds_alternative<std::vector<WofSymbol>>(lhs.value)) {
            const auto& outer = std::get<std::vector<WofSymbol>>(lhs.value);
            if (outer.size() == 3 &&
                std::holds_alternative<std::vector<WofSymbol>>(outer[0].value) &&
                std::holds_alternative<std::string>(outer[1].value) &&
                std::get<std::string>(outer[1].value) == "+" &&
                std::holds_alternative<int64_t>(outer[2].value)) {

                const auto& mulform = std::get<std::vector<WofSymbol>>(outer[0].value);
                if (mulform.size() == 3 &&
                    std::holds_alternative<int64_t>(mulform[0].value) &&
                    std::holds_alternative<std::string>(mulform[1].value) &&
                    std::get<std::string>(mulform[1].value) == "*" &&
                    std::holds_alternative<std::string>(mulform[2].value) &&
                    std::get<std::string>(mulform[2].value) == "X" &&
                    std::holds_alternative<int64_t>(rhs.value)) {

                    int64_t A = std::get<int64_t>(mulform[0].value);
                    int64_t B = std::get<int64_t>(outer[2].value);
                    int64_t C = std::get<int64_t>(rhs.value);
                    int64_t X = (C - B) / A;

                    std::cout << "[solve] X = (" << C << " - " << B << ") / " << A << " = " << X << "\n";
                    vm.pushValue(WofValue(X));
                    return;
                }
            }
        }

        std::cout << "[solve] no matching pattern.\n";
    });
}
