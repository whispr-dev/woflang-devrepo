// load_modelica_constants.cpp
// Loads Modelica-derived constants into WOFLANG

#include "wof_interpreter.hpp"

// Forward declaration of the plugin registration function
void register_mathlib_modelica_constants_plugin(WofInterpreter& vm);

void load_modelica_constants(WofInterpreter& vm) {
    std::cout << "[modelica] Loading Modelica-derived constants..." << std::endl;
    register_mathlib_modelica_constants_plugin(vm);
    std::cout << "[modelica] Constants loaded.\n";
}
