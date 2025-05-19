// repl_units_command.cpp
// Implements :units — list all known registered units

#include "wof_units.hpp"
#include <iostream>

void handle_units_command(const UnitRegistry& reg) {
    std::cout << "[WOFLANG REGISTERED UNITS]\n";
    reg.printAll();
}
