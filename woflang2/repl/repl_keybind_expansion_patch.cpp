// repl_keybind_expansion_patch.cpp
// Expands keybindings into glyphs before REPL parses input

#include "wof_keybinding_core.hpp"
#include <sstream>
#include <string>
#include <vector>

std::string expandKeybindings(const std::string& input, const KeyBindingManager& km) {
    std::istringstream iss(input);
    std::ostringstream oss;
    std::string word;

    while (iss >> word) {
        char32_t g = 0;
        if (km.resolve(word, g)) {
            std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
            oss << conv.to_bytes(g) << " ";
        } else {
            oss << word << " ";
        }
    }

    return oss.str();
}
