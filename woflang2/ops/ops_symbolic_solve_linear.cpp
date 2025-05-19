// ops_symbolic_solve_linear.cpp
// Implements solve(AX = B) → X = B / A

#include "wof_interpreter.hpp"
#include "wof_symbolic.hpp"
#include <iostream>
#include <string>
#include <vector>

void register_symbolic_solve(WofInterpreter& vm) {
    vm.registerOpcode(3201, [](WofInterpreter& vm, const WofToken&) {
        std::cout << "[solve] solving...\n";
        auto eq = vm.popSymbol();  // assuming future vm.popSymbol()

        if (!std::holds_alternative<std::vector<WofSymbol>>(eq.value)) {
            std::cout << "[solve] not a symbolic expression.\n";
            return;
        }

        const auto& tree = std::get<std::vector<WofSymbol>>(eq.value);
        if (tree.size() != 3 || !std::holds_alternative<std::string>(tree[1].value) || std::get<std::string>(tree[1].value) != "=") {
            std::cout << "[solve] not an equation of the form A = B.\n";
            return;
        }

        const auto& lhs = tree[0];
        const auto& rhs = tree[2];

        // Expect lhs to be [2, "*", "X"] and rhs to be int
        if (std::holds_alternative<std::vector<WofSymbol>>(lhs.value)) {
            const auto& lhs_inner = std::get<std::vector<WofSymbol>>(lhs.value);
            if (lhs_inner.size() == 3 &&
                std::holds_alternative<int64_t>(lhs_inner[0].value) &&
                std::holds_alternative<std::string>(lhs_inner[1].value) &&
                std::get<std::string>(lhs_inner[1].value) == "*" &&
                std::holds_alternative<std::string>(lhs_inner[2].value)) {

                int64_t A = std::get<int64_t>(lhs_inner[0].value);
                if (std::holds_alternative<int64_t>(rhs.value)) {
                    int64_t B = std::get<int64_t>(rhs.value);
                    int64_t X = B / A;

                    std::cout << "[solve] " << B << " / " << A << " = " << X << "\n";
                    vm.pushValue(WofValue(X));
                    return;
                }
            }
        }

        std::cout << "[solve] unsupported form or symbol types.\n";
    });
}
