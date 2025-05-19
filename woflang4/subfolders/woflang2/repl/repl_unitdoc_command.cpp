// repl_unitdoc_command.cpp
// Implements :unitdoc — shows how WOFLANG handles units

#include <iostream>

void handle_unitdoc_command() {
    std::cout << "[WOFLANG UNITS: BEHAVIOR OVERVIEW]\n\n";

    std::cout << "-- Arithmetic Behavior --\n";
    std::cout << "10 m + 5 m → 15 m\n";
    std::cout << "10 m + 5 s → [warn] unit mismatch → unitless result\n";
    std::cout << "10 m * 2   → 20 m\n";
    std::cout << "20 kg / 2  → 10 kg\n";

    std::cout << "\n-- Unit Assignment --\n";
    std::cout << "You can define a value with a unit using:\n";
    std::cout << "  push 10 ; push m ; assign_unit\n";

    std::cout << "\n-- Supported Units --\n";
    std::cout << "SI base: m, kg, s, A, K, mol, cd\n";
    std::cout << "Derived: J, N, Pa, V, W, Hz, Ohm\n";
    std::cout << "Prefixes: k (1e3), m (1e-3), μ (1e-6), etc.\n";

    std::cout << "\n-- Access --\n";
    std::cout << ":units       → list current registered units\n";
    std::cout << ":unitdoc     → show this overview\n";
}
