#include "src/core/woflang.hpp"
#include "src/ops/core_ops.hpp" // Add this
#include "src/io/plugin_loader.cpp"
#include <filesystem>
#include <iostream>

int main(int argc, char* argv[]) {
    WoflangInterpreter interp;

    register_core_ops(interp); // Register basic ops - Arithmetic and stack ops
    register_repl_commands(interp); // REPL helper commands

    // Auto-load all plugins in "plugins" dir if it exists
    std::filesystem::path plugin_dir = "plugins";
    if (std::filesystem::exists(plugin_dir))
        load_all_plugins(interp, plugin_dir);

    // CLI: run script if given, else REPL
    if (argc > 1) {
        std::filesystem::path script = argv[1];
        interp.exec_script(script);
        interp.print_stack();
    } else {
        interp.repl();
    }
    return 0;
}
