// wofreplrc_loader_extended.cpp
// Extended config loader: supports watch, autoload, theme

#include "wof_watch_autostart_patch.cpp"
#include "load_woflang_plugins.cpp"
#include "dynamic_glyph_loader.cpp"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

void load_repl_config(WofInterpreter& vm) {
    std::string config_path = std::getenv("HOME") + std::string("/.wofreplrc");
    std::ifstream file(config_path);
    if (!file) {
        std::cout << "[replrc] No config file found at " << config_path << "\n";
        return;
    }

    std::cout << "[replrc] Loading config from " << config_path << "\n";

    std::unordered_map<std::string, std::string> config;

    std::string line;
    while (std::getline(file, line)) {
        auto eq = line.find('=');
        if (eq != std::string::npos) {
            std::string key = line.substr(0, eq);
            std::string value = line.substr(eq + 1);
            config[key] = value;
        }
    }

    if (config["watch"] == "true") {
        start_plugin_autowatch(vm);
    }
    if (config["autoload"] == "true") {
        load_plugin_glyphmaps(vm);
        load_all_woflang_plugins(vm);
    }
    if (config.contains("repltheme")) {
        std::cout << "[replrc] Theme set to: " << config["repltheme"] << "\n";
        // Future: trigger theme switch for REPL UI/console styles
    }
}
