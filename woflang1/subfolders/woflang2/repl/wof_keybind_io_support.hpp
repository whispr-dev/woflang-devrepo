#ifndef WOF_KEYBIND_IO_SUPPORT_HPP
#define WOF_KEYBIND_IO_SUPPORT_HPP

#include "wof_keybinding_core.hpp" // Assuming KeyBindingManager is needed
#include <string>

void loadBindingsFromFile(KeyBindingManager& km);
void saveBindingsToFile(const KeyBindingManager& km); // Assuming saving might be const

#endif // WOF_KEYBIND_IO_SUPPORT_HPP