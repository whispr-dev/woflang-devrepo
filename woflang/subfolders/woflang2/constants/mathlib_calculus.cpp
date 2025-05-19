// mathlib_calculus.cpp
// Implements ∂ (diff) and ∫ (integrate)

#include "wof_interpreter.hpp"
#include <iostream>

void register_mathlib_calculus_plugin(WofInterpreter& vm) {
    vm.registerOpcode(3010, [](WofInterpreter& vm, const WofToken&) {
        int64_t x2 = vm.pop();
        int64_t x1 = vm.pop();
        int64_t dx = x2 - x1;
        vm.push(dx);
        std::cout << "[mathlib] ∂ approximated as (x2 - x1) = " << dx << "\n";
    });

    vm.registerOpcode(3011, [](WofInterpreter& vm, const WofToken&) {
        int64_t b = vm.pop();
        int64_t a = vm.pop();
        int64_t area = (a + b) * (b - a) / 2;
        vm.push(area);
        std::cout << "[mathlib] ∫ approximated as trapezoid area = " << area << "\n";
    });
}
