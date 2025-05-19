// wof_keybind_autoload_patch.cpp
// Hooks binding load/save into REPL lifecycle

// Corrected: Include header files instead of .cpp files
#include "wof_keybind_io_support.hpp"
#include "repl_keybind_command.hpp"
#include "wof_keybinding_core.hpp" // Include this if KeyBindingManager is used directly here
#include <iostream> // For std::cout
#include <string> // For std::string


void load_keybinds(KeyBindingManager& km) {
    loadBindingsFromFile(km);
    std::cout << "[keybind] Loaded ~/.wofbinds\\n"; // Ensure newline is escaped
}

void handle_bind_and_save(KeyBindingManager& km, const std::string& input) {
    handle_keybind_command(km, input);
    saveBindingsToFile(km);
}