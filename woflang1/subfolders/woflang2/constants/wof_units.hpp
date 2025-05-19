// wof_units.hpp
// WOFLANG unit structure (initial scaffold)

#pragma once
#include <string>
#include <iostream>
#include <unordered_map>

struct WofUnit {
    std::string symbol;
    double multiplier = 1.0; // e.g., 1000 for k, 0.001 for m

    void print() const {
        std::cout << "[" << symbol << " ×" << multiplier << "]";
    }
};

class UnitRegistry {
public:
    void registerUnit(const std::string& symbol, double multiplier) {
        units[symbol] = WofUnit{symbol, multiplier};
    }

    const WofUnit* get(const std::string& symbol) const {
        auto it = units.find(symbol);
        return it != units.end() ? &it->second : nullptr;
    }

    void printAll() const {
        for (const auto& [k, v] : units) {
            std::cout << " " << k << " = ×" << v.multiplier << std::endl;
        }
    }

private:
    std::unordered_map<std::string, WofUnit> units;
};
