// repl_physdoc_command.cpp
// Implements :physdoc — lists physics glyph constants

#include <iostream>

void handle_physdoc_command() {
    std::cout << "[WOFLANG PHYSICS CONSTANTS]\n";
    std::cout << "\n-- Physical Constants --\n";
    std::cout << "ℏ     (3060) — Planck's reduced constant\n";
    std::cout << "c      (3061) — Speed of light in vacuum (m/s)\n";
    std::cout << "g      (3062) — Acceleration due to gravity (m/s²)\n";
    std::cout << "e⁻     (3063) — Elementary charge (C)\n";
    std::cout << "mₑ     (3064) — Electron mass (kg)\n";
    std::cout << "mₚ     (3065) — Proton mass (kg)\n";
    std::cout << "R𝑦     (3066) — Rydberg constant (m⁻¹)\n";
}
