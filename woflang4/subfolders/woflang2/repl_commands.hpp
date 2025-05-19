#ifndef REPL_COMMANDS_HPP
#define REPL_COMMANDS_HPP

#include <string>
#include "wof_interpreter.hpp" // For WofInterpreter and potentially BlockRegistry/UnitRegistry if they are members
#include "blocks_and_units.hpp" // For BlockRegistry and UnitRegistry
#include "wof_keybinding_core.hpp" // For KeyBindingManager

// Declarations for REPL command handling functions
void handle_egg_command();
void handle_woflsigil_command();
void handle_woflsigil_variants();
void handle_woflsigil_chaos();
void handle_woflsigil_dream();
void handle_woflsigil_purge(WofInterpreter& vm);
void handle_mathdoc_command();
void handle_physdoc_command();
// Corrected: Declaration using the actual UnitRegistry type
void handle_units_command(UnitRegistry& ur);
void handle_suggest_command(const std::string& line);
void check_suggestion_trigger(const std::string& line);
// Corrected: Declaration using the actual BlockRegistry type
void handle_blocks_command(BlockRegistry& br);
// Corrected: Declaration using the actual BlockRegistry type
void handle_block_tree_command(BlockRegistry& br);
// Corrected: Declaration using the actual BlockRegistry type
void handle_block_lookup_command(BlockRegistry& br, const std::string& line);
void enable_trace();
void disable_trace();
// Corrected: Declaration using the actual KeyBindingManager type
void handle_bind_and_save(KeyBindingManager& kb, const std::string& line);


#endif // REPL_COMMANDS_HPP