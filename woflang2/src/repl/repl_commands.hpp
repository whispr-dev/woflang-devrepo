#pragma once
#include "../core/woflang.hpp"
#include <iostream>

// Register extra REPL commands (suggest, doc, history, etc.)
inline void register_repl_commands(WoflangInterpreter& interp) {
    interp.register_op("help", [](WoflangInterpreter&) {
        std::cout << "Woflang: type arithmetic ops, stack ops, plugin names, or 'exit' to quit.\n";
        std::cout << "Common: + - * / print dup drop swap clear pi e\n";
    });

    interp.register_op("stack", [](WoflangInterpreter& interp) {
        interp.print_stack();
    });

    // You can add history, doc lookup, suggestion, etc. here
}
