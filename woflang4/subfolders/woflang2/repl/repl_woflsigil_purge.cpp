// repl_woflsigil_purge.cpp
// Implements :sigil purge — resets chaos, secrets, and protection flags


#include "wof_interpreter.hpp"
#include <string>
#include <iostream>

void handle_woflsigil_purge(WofInterpreter& interpreter) {
    vm.secretsUnlocked = false;
    interpreter.protectOps(); // Call function
    std::cout << "[SIGIL: PURGE] All chaos flags cleared. The glyphs rest.\n";
    // Other purge logic...
}
