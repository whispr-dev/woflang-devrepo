// mathlib_constants.cpp
// Implements math constants: π (pi), ℯ (e)

#include "wof_interpreter.hpp"
#include <cmath>
#include <iostream>

void register_mathlib_constants_plugin(WofInterpreter& vm) {
    vm.registerOpcode(3001, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(M_PI));
        std::cout << "[mathlib] π pushed to stack\n";
    });

    vm.registerOpcode(3002, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(M_E));
        std::cout << "[mathlib] ℯ pushed to stack\n";
    });
}
