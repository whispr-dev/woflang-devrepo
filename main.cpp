#include "wof_interpreter.hpp"
#include "plugin_loader.cpp"
#include "repl_commands.cpp"

#include <iostream>
#include <string>

int main() {
    WofInterpreter interpreter;
    BlockRegistry blockRegistry;
    KeyBindingManager keybinds;

    load_repl_config(interpreter);
    load_plugin_glyphmaps(interpreter);
    load_all_woflang_plugins(interpreter);
    load_phase1_mathlib_plugins(interpreter);
    load_keybinds(keybinds);
    start_plugin_autowatch(interpreter);

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.starts_with(":bind")) { handle_bind_and_save(keybinds, line); continue; }
        if (line == ":bindings") { keybinds.listBindings(); continue; }
        if (line == ":blocks") { handle_blocks_command(interpreter.blockRegistry); continue; }
        if (line == ":tree") { handle_block_tree_command(interpreter.blockRegistry); continue; }
        if (line.starts_with(":block ")) { handle_block_lookup_command(interpreter.blockRegistry, line); continue; }
        if (line == ":trace") { enable_trace(); continue; }
        if (line == ":untrace") { disable_trace(); continue; }
        if (line == ":mathdoc") { handle_mathdoc_command(); continue; }
        if (line == ":physdoc") { handle_physdoc_command(); continue; }
        if (line == ":units") { handle_units_command(*reinterpret_cast<UnitRegistry*>(nullptr)); continue; } // stub
        if (line.starts_with(":suggest ")) { handle_suggest_command(line); continue; }
        if (line == ":egg") { handle_egg_command(); continue; }
        if (line == ":woflsigil") { handle_woflsigil_command(); continue; }
        if (line == ":sigil ++") { handle_woflsigil_variants(); continue; }
        if (line == ":sigil chaos") { handle_woflsigil_chaos(); continue; }
        if (line == ":sigil dream") { handle_woflsigil_dream(); continue; }
        if (line == ":sigil purge") { handle_woflsigil_purge(interpreter); continue; }
        if (line == ":unlock chaos") {
            interpreter.secretsUnlocked = true;
            std::cout << "[chaos] Forbidden glyphs are now live.\n";
            continue;
        }
        if (interpreter.secretsUnlocked && line.find("☠") != std::string::npos) {
            interpreter.valueStack.clear();
            std::cout << "[☠] Stack slain." << std::endl;
        }

        line = expandKeybindings(line, keybinds);
        check_suggestion_trigger(line);

        // For now just echo
        std::cout << "You entered: " << line << "\n";
    }

    return 0;
}
