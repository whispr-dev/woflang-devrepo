#ifndef PLUGIN_LOADER_HPP
#define PLUGIN_LOADER_HPP

#include "wof_interpreter.hpp" // Assuming WofInterpreter is needed for these functions
#include <string>

// Declarations for plugin loading functions
void load_plugin_glyphmaps(WofInterpreter& vm);
void load_all_woflang_plugins(WofInterpreter& vm);
void load_phase1_mathlib_plugins(WofInterpreter& vm);

#endif // PLUGIN_LOADER_HPP