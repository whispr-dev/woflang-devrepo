#ifndef WOF_KEYBINDING_CORE_HPP
#define WOF_KEYBINDING_CORE_HPP

#include <string>

// Minimal declaration for KeyBindingManager
// You will need to fill this in with the actual class definition from your project
class KeyBindingManager {
public:
    // Assuming a resolve method exists based on repl_keybind_expansion_patch.cpp
    bool resolve(const std::string& key, char32_t& glyph) const;
    // Assuming a listBindings method exists based on main.cpp
    void listBindings() const;
    // Assuming other methods needed for handle_bind_and_save exist
    // ... actual members and methods from your KeyBindingManager class ...
};

// Declaration for load_keybinds function
// Assuming it takes a KeyBindingManager by reference
void load_keybinds(KeyBindingManager& km);


#endif // WOF_KEYBINDING_CORE_HPP