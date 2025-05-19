// repl_keybind_expansion_patch.cpp
// Expands keybindings into glyphs before REPL parses input

#include "wof_keybinding_core.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <locale>   // Required for std::locale and std::use_facet
#include <codecvt>  // Required for std::codecvt_utf8

std::string expandKeybindings(const std::string& input, const KeyBindingManager& km) {
    std::istringstream iss(input);
    std::ostringstream oss;
    std::string word;

    // Corrected: Explicitly get the codecvt_utf8 facet
    // This approach might work around the 'not a member of std' issue in some compilers
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv(
        new std::codecvt_utf8<char32_t>);


    while (iss >> word) {
        char32_t g = 0;
        if (km.resolve(word, g)) {
            oss << conv.to_bytes(g) << " ";
        } else {
            oss << word << " ";
        }
    }

    return oss.str();
}