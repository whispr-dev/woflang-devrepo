#include "../core/woflang.hpp"
#include "../ops/core_ops.hpp"
#include "../repl/repl_commands.hpp"
#include "../math/symbolic_engine.hpp"
#include "../io/plugin_loader.cpp"
#include <filesystem>
#include <iostream>
#include <vector>

// Run all test scripts in /tests, print results and final stack
int main() {
    WoflangInterpreter interp;
    register_core_ops(interp);
    register_repl_commands(interp);
    register_symbolic_ops(interp);

    std::filesystem::path plugin_dir = "../../plugins";
    if (std::filesystem::exists(plugin_dir))
        load_all_plugins(interp, plugin_dir);

    std::vector<std::string> test_scripts = {
        "../../tests/woflang_test_script.wof"
        // Add more as needed
    };

    for (const auto& script : test_scripts) {
        std::cout << "Running: " << script << "\n";
        interp.exec_script(script);
        interp.print_stack();
        interp.clear_stack();
    }
    return 0;
}
