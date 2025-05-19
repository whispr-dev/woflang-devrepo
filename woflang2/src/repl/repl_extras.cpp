#include "repl_helpers.hpp"
#include <iostream>

void register_repl_extras(WoflangInterpreter& interp) {
    // Example: help command
    interp.register_op("help", [](WoflangInterpreter&) {
        std::cout << "WOFLANG REPL commands:\n"
                  << "  help        - this message\n"
                  << "  sigil_map   - list all sacred sigils\n"
                  << "  egg         - joy easter egg\n"
                  << "  prophecy    - sacred prophecy op\n"
                  << "  ...         - see cheatsheet.md\n";
    });
    // Add tab-completion, ritual unlockers, etc. here
}
