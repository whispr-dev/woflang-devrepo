#include "wof_interpreter.hpp"
#include <dlfcn.h>
#include <filesystem>
#include <iostream>

void load_all_woflang_plugins(WofInterpreter& vm) {
    std::string pluginDir = "./plugins/";
    for (const auto& entry : std::filesystem::directory_iterator(pluginDir)) {
        if (entry.path().extension() == ".so") {
            void* handle = dlopen(entry.path().c_str(), RTLD_LAZY);
            if (!handle) {
                std::cerr << "[plugin] Failed to load " << entry.path() << ": " << dlerror() << std::endl;
                continue;
            }

            typedef void (*RegisterFunc)(WofInterpreter&);
            RegisterFunc registerPlugin = (RegisterFunc)dlsym(handle, "register_woflang_plugin");
            if (registerPlugin) {
                registerPlugin(vm);
                std::cout << "[plugin] Registered " << entry.path().filename() << std::endl;
            } else {
                std::cerr << "[plugin] Symbol not found in " << entry.path() << std::endl;
            }
        }
    }
}

void start_plugin_autowatch(WofInterpreter& vm); // declared elsewhere
void load_plugin_glyphmaps(WofInterpreter& vm);  // declared elsewhere
void load_repl_config(WofInterpreter& vm);       // declared elsewhere
void load_phase1_mathlib_plugins(WofInterpreter& vm); // declared elsewhere
void load_keybinds(class KeyBindingManager& kb); // declared elsewhere
