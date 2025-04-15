// wofreplrc_loader.cpp
// Loads a simple config file ~/.wofreplrc with startup flags (e.g. watch=true)

#include "wof_watch_autostart_patch.cpp"
#include <fstream>
#include <iostream>
#include <string>

void load_repl_config(WofInterpreter& vm) {
    std::string config_path = std::getenv("HOME") + std::string("/.wofreplrc");
    std::ifstream file(config_path);
    if (!file) {
        std::cout << "[replrc] No config file found at " << config_path << "\n";
        return;
    }

    std::cout << "[replrc] Loading config from " << config_path << "\n";

    std::string line;
    while (std::getline(file, line)) {
        if (line == "watch=true") {
            start_plugin_autowatch(vm);
        }
    }
}
