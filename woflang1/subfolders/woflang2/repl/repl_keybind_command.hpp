#ifndef REPL_KEYBIND_COMMAND_HPP
#define REPL_KEYBIND_COMMAND_HPP

#include "wof_keybinding_core.hpp" // Assuming KeyBindingManager is needed
#include <string>

void handle_keybind_command(KeyBindingManager& km, const std::string& input);

#endif // REPL_KEYBIND_COMMAND_HPP