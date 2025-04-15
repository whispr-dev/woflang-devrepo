#include "wof_interpreter.hpp"
#include <fstream>
#include <iostream>
#include <string>

void load_repl_config(WofInterpreter& vm) {
    const char* home = getenv("HOME");
    std::string path = std::string(home ? home : ".") + "/.wofreplrc";
    std::ifstream file(path);
    if (!file) {
        std::cout << "[replrc] No config file found at " << path << "
";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == "watch=true") {
            std::cout << "[replrc] Plugin watch enabled.
";
            // could trigger watch_plugins(vm); or set flag
        } else if (line == "autoload=true") {
            std::cout << "[replrc] Autoload enabled.
";
            // no-op: plugins are already auto-loaded in main
        } else if (line.find("repltheme=") == 0) {
            std::string theme = line.substr(10);
            std::cout << "[replrc] Theme set to: " << theme << "
";
            // no actual styling yet, placeholder
        }
    }
}
