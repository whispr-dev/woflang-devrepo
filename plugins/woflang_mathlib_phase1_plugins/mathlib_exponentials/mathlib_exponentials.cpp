#include "wof_interpreter.hpp"
#include <cmath>
#include <iostream>

void register_mathlib_exponentials_plugin(WofInterpreter& vm) {
    vm.registerOpcode(3023, [](WofInterpreter& vm, const WofToken&) {
        std::cout << "[mathlib] exp invoked\n";
        // TODO: Implement exp logic here.
    });
}
