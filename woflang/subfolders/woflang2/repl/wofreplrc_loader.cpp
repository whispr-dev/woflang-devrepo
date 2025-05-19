#include "wof_interpreter.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib> // For _dupenv_s
#include <locale> // Required for _dupenv_s in some environments

void load_repl_config(WofInterpreter& vm) {
    char* home_path = nullptr;
    size_t len;
    // Corrected: Using _dupenv_s for safer environment variable retrieval on Windows
    // Replaces: const char* home = getenv("HOME");
    if (_dupenv_s(&home_path, &len, "HOME") == 0 && home_path != nullptr) {
        std::string path = std::string(home_path) + "/.wofreplrc";
        free(home_path); // Free the allocated buffer
        std::ifstream file(path);
        if (!file) {
            // Corrected: Escaping newline in string literal with \n
            std::cout << "[replrc] No config file found at " << path << "\\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line == "watch=true") {
                // Corrected: Escaping newline in string literal with \n
                std::cout << "[replrc] Plugin watch enabled.\\n";
                // could trigger watch_plugins(vm); or set flag
            } else if (line == "autoload=true") {
                // Corrected: Escaping newline in string literal with \n
                std::cout << "[replrc] Autoload enabled.\\n";
                // no-op: plugins are already auto-loaded in main
            } else if (line.find("repltheme=") == 0) {
                std::string theme = line.substr(10);
                // Corrected: Escaping newline in string literal with \n
                std::cout << "[replrc] Theme set to: " << theme << "\\n";
                // no actual styling yet, placeholder
            }
        }
    } else {
        // Fallback or handle case where HOME is not set
        // Corrected: Escaping newline in string literal with \n
        std::cout << "[replrc] HOME environment variable not set. Skipping config loading.\\n";
    }

}