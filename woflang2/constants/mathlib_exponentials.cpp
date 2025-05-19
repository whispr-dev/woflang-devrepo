// mathlib_exponentials.cpp
// Implements √ (sqrt), ⁒ (pow), ƒlog (log), ƒexp (exp)

#include "wof_interpreter.hpp"
#include <cmath>
#include <iostream>

void register_mathlib_exponentials_plugin(WofInterpreter& vm) {
    vm.registerOpcode(3020, [](WofInterpreter& vm, const WofToken&) {
        double val = vm.pop();
        vm.pushValue(WofValue(std::sqrt(val)));
        std::cout << "[mathlib] √ = " << std::sqrt(val) << "\n";
    });

    vm.registerOpcode(3021, [](WofInterpreter& vm, const WofToken&) {
        double exp = vm.pop();
        double base = vm.pop();
        vm.pushValue(WofValue(std::pow(base, exp)));
        std::cout << "[mathlib] pow(" << base << "," << exp << ")\n";
    });

    vm.registerOpcode(3022, [](WofInterpreter& vm, const WofToken&) {
        double val = vm.pop();
        vm.pushValue(WofValue(std::log(val)));
        std::cout << "[mathlib] log(" << val << ")\n";
    });

    vm.registerOpcode(3023, [](WofInterpreter& vm, const WofToken&) {
        double val = vm.pop();
        vm.pushValue(WofValue(std::exp(val)));
        std::cout << "[mathlib] exp(" << val << ")\n";
    });
}
