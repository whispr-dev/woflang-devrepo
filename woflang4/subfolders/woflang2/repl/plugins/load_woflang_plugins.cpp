// load_woflang_plugins.cpp
// Dynamically loads all .so plugins from ./plugins

#include "wof_interpreter.hpp"
#include <filesystem>
#include <iostream>
#include <dlfcn.h>

namespace fs = std::filesystem;

void load_all_woflang_plugins(WofInterpreter& vm) {
    std::string plugin_dir = "./plugins";
    for (const auto& entry : fs::directory_iterator(plugin_dir)) {
        if (entry.path().extension() == ".so") {
            std::cout << "[plugin loader] Loading " << entry.path().string() << "\n";
            void* handle = dlopen(entry.path().c_str(), RTLD_LAZY);
            if (!handle) {
                std::cerr << "[error] Failed to load " << entry.path().string() << ": " << dlerror() << "\n";
                continue;
            }

            using RegisterFn = void(*)(WofInterpreter&);
            RegisterFn registerPlugin = (RegisterFn)dlsym(handle, "register_woflang_plugin");
            if (!registerPlugin) {
                std::cerr << "[error] Missing 'register_woflang_plugin' symbol in " << entry.path().string() << "\n";
                dlclose(handle);
                continue;
            }

            registerPlugin(vm);  // BOOM: plugin loaded
        }
    }
}
