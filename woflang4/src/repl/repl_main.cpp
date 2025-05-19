#include "woflang.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <cstring>

// Default plugin path (set by CMake)
#ifndef WOFLANG_PLUGIN_PATH
#define WOFLANG_PLUGIN_PATH "./plugins"
#endif

using namespace woflang;

void print_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " [options] [script.wof]\n"
              << "Options:\n"
              << "  -h, --help            Display this help message\n"
              << "  -v, --version         Show version information\n"
              << "  -p, --plugins DIR     Specify an alternative plugins directory\n"
              << "  -l, --list-plugins    List all available plugins\n"
              << "  -n, --no-plugins      Run without loading any plugins\n"
              << "  -i, --interactive     Start REPL after executing script\n"
              << "  --no-sacred           Disable sacred/special operations\n"
              << "  --test                Run all test scripts in the tests directory\n"
              << "\nIf no script is provided, the REPL will start automatically.\n";
}

void print_version() {
    std::cout << "Woflang Interpreter v3.0.0\n"
              << "Copyright (c) 2025 Woflang Team\n"
              << "Licensed under MIT and CC0\n";
}

bool list_plugins(const std::filesystem::path& plugin_dir) {
    std::cout << "Available plugins in " << plugin_dir << ":\n";
    
    bool found = false;
    
    try {
        if (!std::filesystem::exists(plugin_dir)) {
            std::cerr << "Plugin directory does not exist: " << plugin_dir << "\n";
            return false;
        }
        
        for (const auto& entry : std::filesystem::directory_iterator(plugin_dir)) {
            if (!entry.is_regular_file()) continue;
            
            auto path = entry.path();
            auto ext = path.extension().string();
            
        #ifdef WOFLANG_PLATFORM_WINDOWS
            if (ext == ".dll") {
                std::cout << "  * " << path.filename().string() << "\n";
                found = true;
            }
        #else
            if (ext == ".so" || ext == ".dylib") {
                std::cout << "  * " << path.filename().string() << "\n";
                found = true;
            }
        #endif
        }
    } catch (const std::exception& e) {
        std::cerr << "Error listing plugins: " << e.what() << "\n";
        return false;
    }
    
    if (!found) {
        std::cout << "  (No plugins found)\n";
    }
    
    return true;
}

// Run interpreter with command line arguments
int main(int argc, char* argv[]) {
    std::filesystem::path script_path;
    std::filesystem::path plugin_dir = WOFLANG_PLUGIN_PATH;
    bool load_plugins = true;
    bool interactive_mode = false;
    bool sacred_ops = true;
    bool test_mode = false;
    
    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            print_version();
            return 0;
        } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--plugins") == 0) {
            if (i + 1 < argc) {
                plugin_dir = argv[++i];
            } else {
                std::cerr << "Error: Missing directory after " << argv[i] << "\n";
                return 1;
            }
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--list-plugins") == 0) {
            if (list_plugins(plugin_dir)) {
                return 0;
            } else {
                return 1;
            }
        } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--no-plugins") == 0) {
            load_plugins = false;
        } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--interactive") == 0) {
            interactive_mode = true;
        } else if (strcmp(argv[i], "--no-sacred") == 0) {
            sacred_ops = false;
        } else if (strcmp(argv[i], "--test") == 0) {
            test_mode = true;
        } else if (argv[i][0] == '-') {
            std::cerr << "Error: Unknown option " << argv[i] << "\n";
            print_usage(argv[0]);
            return 1;
        } else {
            // Assume it's a script file
            script_path = argv[i];
        }
    }
    
    try {
        // Create interpreter
        WoflangInterpreter interp;
        
        // Load plugins if requested
        if (load_plugins) {
            try {
                interp.load_plugins(plugin_dir);
            } catch (const std::exception& e) {
                std::cerr << "Warning: Failed to load plugins: " << e.what() << "\n";
                std::cerr << "Continuing without plugins...\n";
            }
        }
        
        // Execute script file if provided
        if (!script_path.empty()) {
            try {
                interp.exec_script(script_path);
            } catch (const std::exception& e) {
                std::cerr << "Error executing script: " << e.what() << "\n";
                return 1;
            }
        }
        
        // Run tests if requested
        if (test_mode) {
            std::cout << "Running tests...\n";
            std::filesystem::path test_dir = "tests";
            
            if (!std::filesystem::exists(test_dir)) {
                std::cerr << "Test directory does not exist: " << test_dir << "\n";
                return 1;
            }
            
            bool all_passed = true;
            
            for (const auto& entry : std::filesystem::directory_iterator(test_dir)) {
                if (!entry.is_regular_file()) continue;
                
                auto path = entry.path();
                if (path.extension() == ".wof") {
                    std::cout << "Running test: " << path.filename().string() << "... ";
                    try {
                        WoflangInterpreter test_interp;
                        if (load_plugins) {
                            test_interp.load_plugins(plugin_dir);
                        }
                        test_interp.exec_script(path);
                        std::cout << "PASSED\n";
                    } catch (const std::exception& e) {
                        std::cout << "FAILED: " << e.what() << "\n";
                        all_passed = false;
                    }
                }
            }
            
            if (all_passed) {
                std::cout << "All tests passed!\n";
            } else {
                std::cout << "Some tests failed.\n";
                return 1;
            }
            
            return all_passed ? 0 : 1;
        }
        
        // Start REPL if no script or interactive mode requested
        if (script_path.empty() || interactive_mode) {
            interp.repl();
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}