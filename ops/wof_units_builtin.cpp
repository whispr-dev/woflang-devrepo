// wof_units_builtin.cpp
// Registers default SI and base units in WOFLANG

#include "wof_units.hpp"
#include <iostream>

void register_builtin_units(UnitRegistry& reg) {
    std::cout << "[units] Loading SI base units...\n";

    // Base units
    reg.registerUnit("m", 1.0);     // meter
    reg.registerUnit("kg", 1.0);    // kilogram
    reg.registerUnit("s", 1.0);     // second
    reg.registerUnit("A", 1.0);     // ampere
    reg.registerUnit("K", 1.0);     // kelvin
    reg.registerUnit("mol", 1.0);   // mole
    reg.registerUnit("cd", 1.0);    // candela

    // Derived units
    reg.registerUnit("Hz", 1.0);    // Hertz
    reg.registerUnit("N", 1.0);     // Newton
    reg.registerUnit("J", 1.0);     // Joule
    reg.registerUnit("W", 1.0);     // Watt
    reg.registerUnit("Pa", 1.0);    // Pascal
    reg.registerUnit("V", 1.0);     // Volt
    reg.registerUnit("Ohm", 1.0);   // Ohm
    reg.registerUnit("lm", 1.0);    // Lumen
    reg.registerUnit("lx", 1.0);    // Lux

    // SI prefixes (can be combined manually for now)
    reg.registerUnit("k", 1e3);     // kilo
    reg.registerUnit("M", 1e6);     // mega
    reg.registerUnit("G", 1e9);     // giga
    reg.registerUnit("m", 1e-3);    // milli
    reg.registerUnit("μ", 1e-6);    // micro
    reg.registerUnit("n", 1e-9);    // nano
    reg.registerUnit("p", 1e-12);   // pico

    std::cout << "[units] Base unit set registered.\n";
}
