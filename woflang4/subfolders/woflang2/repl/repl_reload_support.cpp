// repl_reload_support.cpp
// Adds :reload REPL command to reload all plugins and glyphmaps

#include "load_woflang_plugins.cpp"
#include "dynamic_glyph_loader.cpp"

void handle_repl_reload(WofInterpreter& vm) {
    std::cout << "[repl] Reloading plugins and glyphmaps...\n";
    glyphToOpcode.clear();
    load_plugin_glyphmaps(vm);
    load_all_woflang_plugins(vm);
    std::cout << "[repl] Reload complete.\n";
}
