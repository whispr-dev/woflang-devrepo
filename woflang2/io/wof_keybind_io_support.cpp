// wof_keybind_io_support.cpp
// Loads and saves keybindings from ~/.wofbinds

#include "wof_keybinding_core.hpp"
#include <fstream>
#include <string>
#include <sstream>

void loadBindingsFromFile(KeyBindingManager& km, const std::string& path = std::string(getenv("HOME")) + "/.wofbinds") {
    std::ifstream file(path);
    if (!file) return;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string alias, glyphUTF8;
        if (iss >> alias >> glyphUTF8) {
            std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
            char32_t glyph = conv.from_bytes(glyphUTF8)[0];
            km.bind(alias, glyph);
        }
    }
}

void saveBindingsToFile(const KeyBindingManager& km, const std::string& path = std::string(getenv("HOME")) + "/.wofbinds") {
    std::ofstream out(path);
    if (!out) return;

    for (const auto& [alias, glyph] : km.getAll()) {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
        out << alias << " " << conv.to_bytes(glyph) << "\n";
    }
}
