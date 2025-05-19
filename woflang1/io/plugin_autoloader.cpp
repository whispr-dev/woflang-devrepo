#include "../core/woflang.hpp"
#include "plugin_loader.cpp"
#include <filesystem>
#include <iostream>

int main(int argc, char* argv[]) {
    WoflangInterpreter interp;
    std::filesystem::path plugin_dir = "../../plugins";
    if (!std::filesystem::exists(plugin_dir)) {
        std::cout << "No plugins directory found at " << plugin_dir << "\n";
        return 1;
    }
    load_all_plugins(interp, plugin_dir);
    std::cout << "Loaded plugins: " << interp.plugin_handles.size() << "\n";
    // Optionally test: list all ops
    std::cout << "Available ops:\n";
    for (const auto& [name, _] : interp.op_handlers)
        std::cout << "  " << name << "\n";
    return 0;
}
