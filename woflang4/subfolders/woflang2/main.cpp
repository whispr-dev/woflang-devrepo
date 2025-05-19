#include "wof_interpreter.hpp"
#include "plugin_loader.hpp"
#include "repl/woflreplrc_loader.hpp"
#include "repl/repl_keybind_expansion_patch.hpp"
#include "repl/repl_plugin_watch_support.hpp"
#include "repl_commands.hpp"
#include "blocks_and_units.hpp"
#include "wofl_keybinding_core.hpp"

#include <string>
#include <iostream>

int main() {
    WofInterpreter interpreter;
    KeyBindingManager keybinds;
    BlockRegistry blockRegistry;
    UnitRegistry unitRegistry;

    // Load configurations and plugins
    load_repl_config(interpreter);
    load_plugin_glyphmaps(interpreter);
    load_all_woflang_plugins(interpreter);
    load_phase1_mathlib_plugins(interpreter);
    load_keybinds(keybinds);
    watch_plugins(interpreter);

    // REPL loop
    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "exit") break;

        // Example commands
        if (input == "blocks") {
            handle_blocks_command(blockRegistry);
        } else if (input == "tree") {
            handle_block_tree_command(blockRegistry);
        } else if (input.find("lookup ") == 0) {
            handle_block_lookup_command(blockRegistry, input.substr(7));
        } else if (input == "units") {
            handle_units_command(unitRegistry);
        }
    }

    return 0;
}