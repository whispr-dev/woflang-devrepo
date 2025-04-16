#include "wof_interpreter.hpp"
#include <windows.h>
#include <iostream>
#include <filesystem>

using std::string;
namespace fs = std::filesystem;

void loadPlugins(WofInterpreter& vm, const string& pluginDir = "plugins") {
    for (const auto& entry : fs::directory_iterator(pluginDir)) {
        if (entry.path().extension() != ".dll" && entry.path().extension() != ".so")
            continue;

        std::string path = entry.path().string();
        std::cout << "[plugin_loader] Loading plugin: " << path << "\n";

        HMODULE handle = LoadLibraryA(path.c_str());
        if (!handle) {
            std::cerr << "[plugin_loader] Failed to load: " << path << "\n";
            continue;
        }

        auto register_fn = (void (*)(WofInterpreter&)) GetProcAddress(handle, "register_woflang_plugin");
        if (!register_fn) {
            std::cerr << "[plugin_loader] Missing register_woflang_plugin symbol in: " << path << "\n";
            continue;
        }

        register_fn(vm);
        std::cout << "[plugin_loader] Plugin loaded: " << path << "\n";
    }
}
