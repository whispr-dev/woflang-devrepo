#ifndef REPL_PLUGIN_WATCH_SUPPORT_HPP
#define REPL_PLUGIN_WATCH_SUPPORT_HPP

#include "wof_interpreter.hpp" // Assuming WofInterpreter is needed
#include <string>
#include <thread> // watch_plugins likely uses threading
#include <filesystem> // watch_plugins uses filesystem

// Declaration for the plugin watch function
// Assuming start_plugin_autowatch is either this function or calls it
// Based on the previous .cpp, watch_plugins takes WofInterpreter by reference.
void watch_plugins(WofInterpreter& vm, const std::string& folder = "./plugins");

// If start_plugin_autowatch is a separate function that e.g. manages the thread:
// void start_plugin_autowatch(WofInterpreter& vm);


#endif // REPL_PLUGIN_WATCH_SUPPORT_HPP