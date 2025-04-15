// wof_keybind_autoload_patch.cpp
// Hooks binding load/save into REPL lifecycle

#include "wof_keybind_io_support.cpp"
#include "repl_keybind_command.cpp"

void load_keybinds(KeyBindingManager& km) {
    loadBindingsFromFile(km);
    std::cout << "[keybind] Loaded ~/.wofbinds\n";
}

void handle_bind_and_save(KeyBindingManager& km, const std::string& input) {
    handle_keybind_command(km, input);
    saveBindingsToFile(km);
}
