// mathlib_modelica_constants.cpp
// Constants inspired by Modelica Standard Library

#include "wof_interpreter.hpp"
#include <iostream>
#include <cmath>

void register_mathlib_modelica_constants_plugin(WofInterpreter& vm) {
    vm.registerOpcode(3050, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(2 * M_PI));
        std::cout << "[modelica] pi2 = 2π pushed\n";
    });

    vm.registerOpcode(3051, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(2.220446049250313e-15));  // 10 * DBL_EPSILON approx
        std::cout << "[modelica] eps ≈ 10ε pushed\n";
    });

    vm.registerOpcode(3052, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(715827883));
        std::cout << "[modelica] localSeed pushed\n";
    });

    vm.registerOpcode(3053, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(10));
        std::cout << "[modelica] p = 10 (iterations) pushed\n";
    });

    vm.registerOpcode(3054, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(33));
        std::cout << "[modelica] nState = 33 pushed\n";
    });
}
