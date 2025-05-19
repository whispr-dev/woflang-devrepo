// repl_keybind_command.cpp
// Adds :bind and :bindings to REPL

#include "wof_keybinding_core.hpp"
#include <sstream>

void handle_keybind_command(KeyBindingManager& km, const std::string& input) {
    std::istringstream iss(input);
    std::string cmd, alias, glyphUTF8;
    iss >> cmd >> alias >> glyphUTF8;

    if (cmd == ":bind" && !alias.empty() && !glyphUTF8.empty()) {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
        char32_t glyph = conv.from_bytes(glyphUTF8)[0];
        km.bind(alias, glyph);
        std::cout << "[bind] " << alias << " bound to " << static_cast<char32_t>(glyph) << "\n";
    } else if (cmd == ":bindings") {
        km.listBindings();
    } else {
        std::cout << "[bind] Usage: :bind alias glyph   or   :bindings\n";
    }
}
