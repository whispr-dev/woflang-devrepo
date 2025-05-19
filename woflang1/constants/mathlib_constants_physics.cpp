// mathlib_constants_physics.cpp
// Physics constants from WOFLANG textbook sources

#include "wof_interpreter.hpp"
#include <iostream>

void register_mathlib_physics_constants_plugin(WofInterpreter& vm) {
    vm.registerOpcode(3060, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(1.0545718e-34));  // ℏ
        std::cout << "[physics] ℏ pushed\n";
    });

    vm.registerOpcode(3061, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(299792458));  // c
        std::cout << "[physics] c = speed of light pushed\n";
    });

    vm.registerOpcode(3062, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(9.807));  // g
        std::cout << "[physics] g = gravity pushed\n";
    });

    vm.registerOpcode(3063, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(1.602176634e-19));  // elementary charge
        std::cout << "[physics] e⁻ charge pushed\n";
    });

    vm.registerOpcode(3064, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(9.1093835611e-31));  // m_e
        std::cout << "[physics] mₑ = electron mass pushed\n";
    });

    vm.registerOpcode(3065, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(1.67262192369e-27));  // m_p
        std::cout << "[physics] mₚ = proton mass pushed\n";
    });

    vm.registerOpcode(3066, [](WofInterpreter& vm, const WofToken&) {
        vm.pushValue(WofValue(10973731.56850865));  // Rydberg
        std::cout << "[physics] Rydberg constant pushed\n";
    });
}
