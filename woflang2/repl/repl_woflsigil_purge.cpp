// repl_woflsigil_purge.cpp
// Implements :sigil purge — resets chaos, secrets, and protection flags

#include "wof_interpreter.hpp"
#include <iostream>

void handle_woflsigil_purge(WofInterpreter& vm) {
    vm.secretsUnlocked = false;
    vm.protectOps = false;
    std::cout << "[SIGIL: PURGE] All chaos flags cleared. The glyphs rest.\n";
}
