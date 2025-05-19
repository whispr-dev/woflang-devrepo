/**
 * @file woflang.cpp
 * @brief Implementation of the core Woflang interpreter
 */

#include "woflang.hpp"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <regex>
#include <stdexcept>
#include <filesystem>

namespace woflang {

WoflangInterpreter::WoflangInterpreter() {
    // Constructor. Core ops are registered separately via register_core_ops()
    // to keep the code modular
}

WoflangInterpreter::~WoflangInterpreter() {
    // Clean up plugin handles
    for (auto handle : plugin_handles) {
#ifdef WOFLANG_PLATFORM_WINDOWS
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
    }
    plugin_handles.clear();
}

void WoflangInterpreter::register_op(const std::string& name, WofOpHandler handler) {
    op_handlers[name] = std::move(handler);
}

void WoflangInterpreter::load_plugin(const std::filesystem::path& dll_path) {
    // Load a plugin DLL/shared library
#ifdef WOFLANG_PLATFORM_WINDOWS
    HMODULE handle = LoadLibraryW(dll_path.wstring().c_str());
    if (!handle) {
        DWORD error = GetLastError();
        throw std::runtime_error("Failed to load plugin: " + dll_path.string() + 
                                 " (Error code: " + std::to_string(error) + ")");
    }

    // Look up the register_plugin function
    auto register_func = reinterpret_cast<RegisterPluginFunc>(
        GetProcAddress(handle, "register_plugin"));
    
    if (!register_func) {
        DWORD error = GetLastError();
        FreeLibrary(handle);
        throw std::runtime_error("Plugin missing required 'register_plugin' function: " + 
                                 dll_path.string() + " (Error code: " + std::to_string(error) + ")");
    }
#else
    void* handle = dlopen(dll_path.c_str(), RTLD_LAZY);
    if (!handle) {
        throw std::runtime_error("Failed to load plugin: " + dll_path.string() + 
                                 " (" + dlerror() + ")");
    }

    // Look up the register_plugin function
    auto register_func = reinterpret_cast<RegisterPluginFunc>(
        dlsym(handle, "register_plugin"));
    
    if (!register_func) {
        std::string error = dlerror();
        dlclose(handle);
        throw std::runtime_error("Plugin missing required 'register_plugin' function: " + 
                                 dll_path.string() + " (" + error + ")");
    }
#endif

    // Call the plugin's registration function
    register_func(*this);
    
    // Store the handle for later cleanup
    plugin_handles.push_back(handle);
}

void WoflangInterpreter::load_plugins(const std::filesystem::path& plugin_dir) {
    // Load all plugins in a directory
    if (!std::filesystem::exists(plugin_dir)) {
        error("Plugin directory not found: " + plugin_dir.string());
        return;
    }

    for (const auto& entry : std::filesystem::directory_iterator(plugin_dir)) {
#ifdef WOFLANG_PLATFORM_WINDOWS
        if (entry.path().extension() == ".dll") {
#else
        if (entry.path().extension() == ".so" || entry.path().extension() == ".dylib") {
#endif
            try {
                load_plugin(entry.path());
                std::cout << "Loaded plugin: " << entry.path().filename().string() << std::endl;
            } catch (const std::exception& e) {
                error("Plugin load failed: " + std::string(e.what()));
            }
        }
    }
}

std::vector<std::string> WoflangInterpreter::tokenize(const std::string& line) {
    // Simple tokenizer that splits on whitespace and handles quoted strings
    std::vector<std::string> tokens;
    std::string token;
    bool in_quotes = false;
    
    for (char c : line) {
        if (c == '"') {
            in_quotes = !in_quotes;
            token += c;
        } else if (std::isspace(c) && !in_quotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }
    
    if (!token.empty()) {
        tokens.push_back(token);
    }
    
    return tokens;
}

void WoflangInterpreter::dispatch_token(const std::string& token) {
    // First, check if it's an operation
    auto it = op_handlers.find(token);
    if (it != op_handlers.end()) {
        // It's an operation, execute it
        try {
            it->second(*this);
        } catch (const std::exception& e) {
            error("Error executing operation '" + token + "': " + e.what());
        }
        return;
    }
    
    // Try to parse as a number
    try {
        // Check if it's an integer
        size_t pos = 0;
        int64_t int_val = std::stoll(token, &pos);
        if (pos == token.size()) {
            // Successfully parsed as integer
            stack.emplace_back(int_val);
            return;
        }
        
        // Check if it's a double
        double double_val = std::stod(token, &pos);
        if (pos == token.size()) {
            // Successfully parsed as double
            stack.emplace_back(double_val);
            return;
        }
    } catch (const std::exception&) {
        // Not a number, continue
    }
    
    // If it's a quoted string, parse it as a string
    if (token.size() >= 2 && token.front() == '"' && token.back() == '"') {
        stack.emplace_back(token.substr(1, token.size() - 2));
        return;
    }
    
    // Otherwise, it's a symbol
    stack.emplace_back(token, WofType::Symbol);
}

void WoflangInterpreter::exec_line(const std::string& line) {
    // Skip empty lines and comments
    if (line.empty() || line[0] == '#') {
        return;
    }
    
    // Tokenize and execute each token
    auto tokens = tokenize(line);
    for (const auto& token : tokens) {
        try {
            dispatch_token(token);
        } catch (const std::exception& e) {
            error(e.what());
        }
    }
}

void WoflangInterpreter::exec_script(const std::filesystem::path& filename) {
    // Execute a script file
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Cannot open script file: " + filename.string());
    }
    
    std::string line;
    int line_num = 0;
    
    while (std::getline(file, line)) {
        line_num++;
        try {
            exec_line(line);
        } catch (const std::exception& e) {
            error("Error in line " + std::to_string(line_num) + ": " + e.what());
        }
    }
}

void WoflangInterpreter::repl() {
    // Start a Read-Eval-Print Loop
    std::string line;
    std::cout << "woflang REPL (type 'exit' or Ctrl+C to quit)\n";
    
    while (true) {
        std::cout << ">> ";
        if (!std::getline(std::cin, line)) {
            break;  // EOF or error
        }
        
        if (line == "exit") {
            break;
        }
        
        try {
            exec_line(line);
            print_stack();
        } catch (const std::exception& e) {
            error(e.what());
        }
    }
}

void WoflangInterpreter::print_stack() const {
    // Display the current stack
    std::cout << "Stack [";
    for (size_t i = 0; i < stack.size(); ++i) {
        std::cout << stack[i].to_string();
        if (i < stack.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

void WoflangInterpreter::clear_stack() {
    // Clear the stack
    stack.clear();
}

void WoflangInterpreter::error(const std::string& msg) {
    // Report an error
    std::cerr << "Error: " << msg << std::endl;
}

} // namespace woflang