#include "wof_interpreter.hpp"
#include <cmath>
#include <iostream>

void register_mathlib_constants_plugin(WofInterpreter& vm) {
    vm.registerOpcode(3002, [](WofInterpreter& vm, const WofToken&) {
        std::cout << "[mathlib] e invoked\n";
        // TODO: Implement e logic here.
    });
}
