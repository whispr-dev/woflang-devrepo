// load_phase1_mathlib_plugins.cpp
// Registers all Phase 1 mathlib plugins

#include "wof_interpreter.hpp"

// Forward declarations
void register_mathlib_constants_plugin(WofInterpreter& vm);
void register_mathlib_calculus_plugin(WofInterpreter& vm);
void register_mathlib_exponentials_plugin(WofInterpreter& vm);

void load_phase1_mathlib_plugins(WofInterpreter& vm) {
    std::cout << "[mathlib] Loading Phase 1 core plugins..." << std::endl;
    register_mathlib_constants_plugin(vm);
    register_mathlib_calculus_plugin(vm);
    register_mathlib_exponentials_plugin(vm);
    std::cout << "[mathlib] Phase 1 core loaded." << std::endl;
}
