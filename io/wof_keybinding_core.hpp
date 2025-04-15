// wof_keybinding_core.hpp
// Manages keybinding aliases (e.g. "df" => ∂)

#pragma once
#include <unordered_map>
#include <string>
#include <iostream>

class KeyBindingManager {
public:
    void bind(const std::string& alias, char32_t glyph) {
        bindings[alias] = glyph;
    }

    bool resolve(const std::string& alias, char32_t& out) const {
        auto it = bindings.find(alias);
        if (it != bindings.end()) {
            out = it->second;
            return true;
        }
        return false;
    }

    void listBindings() const {
        std::cout << "[BINDINGS]\n";
        for (const auto& [k, v] : bindings) {
            std::cout << k << " → " << static_cast<char32_t>(v) << "\n";
        }
    }

private:
    std::unordered_map<std::string, char32_t> bindings;
};
