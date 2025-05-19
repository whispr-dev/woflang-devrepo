// load_physics_constants.cpp
// Loads WOFLANG physics constants plugin

#include "wof_interpreter.hpp"

// Forward declaration
void register_mathlib_physics_constants_plugin(WofInterpreter& vm);

void load_physics_constants(WofInterpreter& vm) {
    std::cout << "[physics] Loading physics constants..." << std::endl;
    register_mathlib_physics_constants_plugin(vm);
    std::cout << "[physics] Constants loaded.\n";
}
