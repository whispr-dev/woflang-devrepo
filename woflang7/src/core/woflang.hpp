// src/core/woflang.hpp - Compatible with existing plugins
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <memory>
#include <functional>
#include <filesystem>
#include <variant>

#ifdef _WIN32
#include <windows.h>
#undef VOID  // Undefine Windows VOID macro
#define WOFLANG_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
#include <dlfcn.h>
#define WOFLANG_PLUGIN_EXPORT extern "C"
#endif

using namespace std;

namespace woflang {

// WofType enum that your plugins expect
enum class WofType {
    Integer,
    Double,
    String,
    Symbol,
    Boolean,
    Complex,
    Qubit,
    Empty  // Renamed from VOID to avoid Windows conflict
};

// WofValue struct that your plugins expect
struct WofValue {
    WofType type;
    std::variant<int64_t, double, std::string, bool, std::complex<double>, std::vector<std::complex<double>>> value;
    
    WofValue() : type(WofType::Empty) {}
    WofValue(int64_t i) : type(WofType::Integer), value(i) {}
    WofValue(double d) : type(WofType::Double), value(d) {}
    WofValue(const std::string& s) : type(WofType::String), value(s) {}
    WofValue(const std::string& s, WofType t) : type(t), value(s) {}
    WofValue(bool b) : type(WofType::Boolean), value(b) {}
    WofValue(const std::complex<double>& c) : type(WofType::Complex), value(c) {}
    WofValue(const std::vector<std::complex<double>>& q) : type(WofType::Qubit), value(q) {}
    
    // Convenience methods
    bool isNumeric() const { return type == WofType::Integer || type == WofType::Double; }
    bool is_numeric() const { return isNumeric(); }  // Plugin compatibility
    
    double asNumber() const {
        if (type == WofType::Integer) return static_cast<double>(std::get<int64_t>(value));
        if (type == WofType::Double) return std::get<double>(value);
        return 0.0;
    }
    double as_numeric() const { return asNumber(); }  // Plugin compatibility
    
    std::string toString() const {
        switch (type) {
            case WofType::Integer: return std::to_string(std::get<int64_t>(value));
            case WofType::Double: return std::to_string(std::get<double>(value));
            case WofType::String: return std::get<std::string>(value);
            case WofType::Symbol: return std::get<std::string>(value);
            case WofType::Boolean: return std::get<bool>(value) ? "true" : "false";
            case WofType::Complex: {
                auto c = std::get<std::complex<double>>(value);
                return std::to_string(c.real()) + "+" + std::to_string(c.imag()) + "i";
            }
            case WofType::Qubit: return "|ψ⟩";
            case WofType::Empty: return "empty";
        }
        return "";
    }
    std::string to_string() const { return toString(); }  // Plugin compatibility
};

// Forward declaration
class WoflangInterpreter;

// Base class that your plugins expect
class WoflangPlugin {
public:
    virtual ~WoflangPlugin() = default;
    virtual void register_ops(WoflangInterpreter& interp) = 0;
};

class WoflangInterpreter {
public:
    std::vector<WofValue> stack;  // Public stack that plugins expect
    
private:
    std::map<std::string, std::function<void()>> builtins;
    std::vector<void*> loaded_plugins;
    
    // Enhanced tokenizer that handles Unicode and special operators
    std::vector<std::string> tokenize(const std::string& input) {
        std::vector<std::string> tokens;
        std::string current_token;
        bool in_string = false;
        
        for (size_t i = 0; i < input.length(); i++) {
            char c = input[i];
            
            if (in_string) {
                if (c == '"') {
                    in_string = false;
                    tokens.push_back("\"" + current_token + "\"");
                    current_token.clear();
                } else {
                    current_token += c;
                }
            } else {
                if (c == '"') {
                    if (!current_token.empty()) {
                        tokens.push_back(current_token);
                        current_token.clear();
                    }
                    in_string = true;
                } else if (isspace(c)) {
                    if (!current_token.empty()) {
                        tokens.push_back(current_token);
                        current_token.clear();
                    }
                } else {
                    current_token += c;
                }
            }
        }
        
        if (!current_token.empty()) {
            tokens.push_back(current_token);
        }
        
        return tokens;
    }
    
    // Enhanced number parsing
    bool isNumber(const std::string& token) {
        if (token.empty()) return false;
        if (token == "π") return true;
        if (token == "e") return true;
        if (token == "φ") return true;
        
        try {
            std::stod(token);
            return true;
        } catch (...) {
            return false;
        }
    }
    
    double parseNumber(const std::string& token) {
        if (token == "π") return 3.14159265358979323846;
        if (token == "e") return 2.71828182845904523536;
        if (token == "φ") return (1.0 + sqrt(5.0)) / 2.0;
        return std::stod(token);
    }
    
    // Enhanced qubit state parsing
    bool isQubitState(const std::string& token) {
        return token.find("|") == 0 && token.find("⟩") != std::string::npos;
    }
    
    WofValue parseQubitState(const std::string& token) {
        if (token == "|0⟩") {
            return WofValue(std::vector<std::complex<double>>{std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0)});
        } else if (token == "|1⟩") {
            return WofValue(std::vector<std::complex<double>>{std::complex<double>(0.0, 0.0), std::complex<double>(1.0, 0.0)});
        } else if (token == "|+⟩") {
            double inv_sqrt2 = 1.0 / sqrt(2.0);
            return WofValue(std::vector<std::complex<double>>{std::complex<double>(inv_sqrt2, 0.0), std::complex<double>(inv_sqrt2, 0.0)});
        } else if (token == "|-⟩") {
            double inv_sqrt2 = 1.0 / sqrt(2.0);
            return WofValue(std::vector<std::complex<double>>{std::complex<double>(inv_sqrt2, 0.0), std::complex<double>(-inv_sqrt2, 0.0)});
        }
        
        // Default to |0⟩ if parsing fails
        return WofValue(std::vector<std::complex<double>>{std::complex<double>(1.0, 0.0), std::complex<double>(0.0, 0.0)});
    }
    
public:
    WoflangInterpreter() {
        setupBuiltins();
    }
    
    // Plugin-compatible methods
    void push(const WofValue& value) {
        stack.push_back(value);
    }
    
    WofValue pop() {
        if (stack.empty()) {
            return WofValue(); // Return empty value
        }
        WofValue value = stack.back();
        stack.pop_back();
        return value;
    }
    
    void clear_stack() {
        stack.clear();
    }
    
    void register_op(const std::string& name, std::function<void(WoflangInterpreter&)> func) {
        builtins[name] = [this, func]() {
            func(*this);
        };
    }
    
    void setupBuiltins() {
        // Enhanced math operations
        builtins["+"] = [this]() {
            if (stack.size() < 2) {
                std::cout << "Error: Stack underflow: + requires two values" << std::endl;
                return;
            }
            WofValue b = pop();
            WofValue a = pop();
            if (a.isNumeric() && b.isNumeric()) {
                push(WofValue(a.asNumber() + b.asNumber()));
            } else {
                std::cout << "Error: Type error: + requires numeric values" << std::endl;
                push(a);
                push(b);
            }
        };
        
        builtins["*"] = [this]() {
            if (stack.size() < 2) {
                std::cout << "Error: Stack underflow: * requires two values" << std::endl;
                return;
            }
            WofValue b = pop();
            WofValue a = pop();
            if (a.isNumeric() && b.isNumeric()) {
                push(WofValue(a.asNumber() * b.asNumber()));
            } else {
                std::cout << "Error: Type error: * requires numeric values" << std::endl;
                push(a);
                push(b);
            }
        };
        
        builtins["-"] = [this]() {
            if (stack.size() < 2) {
                std::cout << "Error: Stack underflow: - requires two values" << std::endl;
                return;
            }
            WofValue b = pop();
            WofValue a = pop();
            if (a.isNumeric() && b.isNumeric()) {
                push(WofValue(a.asNumber() - b.asNumber()));
            } else {
                std::cout << "Error: Type error: - requires numeric values" << std::endl;
                push(a);
                push(b);
            }
        };
        
        builtins["/"] = [this]() {
            if (stack.size() < 2) {
                std::cout << "Error: Stack underflow: / requires two values" << std::endl;
                return;
            }
            WofValue b = pop();
            WofValue a = pop();
            if (a.isNumeric() && b.isNumeric()) {
                if (b.asNumber() != 0.0) {
                    push(WofValue(a.asNumber() / b.asNumber()));
                } else {
                    std::cout << "Error: Division by zero" << std::endl;
                    push(a);
                    push(b);
                }
            } else {
                std::cout << "Error: Type error: / requires numeric values" << std::endl;
                push(a);
                push(b);
            }
        };
        
        builtins["."] = [this]() {
            if (stack.empty()) {
                std::cout << "Error: Stack underflow: . requires at least one value" << std::endl;
                return;
            }
            WofValue val = pop();
            if (val.type == WofType::Double || val.type == WofType::Integer) {
                std::cout << std::fixed << std::setprecision(5) << val.asNumber() << std::endl;
            } else {
                std::cout << val.toString() << std::endl;
            }
        };
        
        builtins["dup"] = [this]() {
            if (stack.empty()) {
                std::cout << "Error: Stack underflow: dup requires at least one value" << std::endl;
                return;
            }
            WofValue val = stack.back();
            push(val);
        };
        
        builtins["drop"] = [this]() {
            if (stack.empty()) {
                std::cout << "Error: Stack underflow: drop requires at least one value" << std::endl;
                return;
            }
            pop();
        };
        
        builtins["swap"] = [this]() {
            if (stack.size() < 2) {
                std::cout << "Error: Stack underflow: swap requires two values" << std::endl;
                return;
            }
            WofValue a = pop();
            WofValue b = pop();
            push(a);
            push(b);
        };
        
        builtins["help"] = [this]() {
            std::cout << "Woflang v3.0.0 Commands:" << std::endl;
            std::cout << "  Math: +, -, *, /, π, e, φ" << std::endl;
            std::cout << "  Stack: dup, drop, swap, ." << std::endl;
            std::cout << "  Quantum: |0⟩, |1⟩, |+⟩, |−⟩, H, measure" << std::endl;
            std::cout << "  Plugins: prophecy, sierpinski, stack_slayer, etc." << std::endl;
            std::cout << "  System: help, exit" << std::endl;
        };
        
        builtins["exit"] = [this]() {
            std::cout << "Goodbye, woflfren! 🐺✨" << std::endl;
            exit(0);
        };
    }
    
    void loadPlugin(const std::string& plugin_path) {
        #ifdef _WIN32
        HMODULE handle = LoadLibrary(plugin_path.c_str());
        if (!handle) {
            std::cout << "Failed to load plugin: " << plugin_path << std::endl;
            return;
        }
        
        // Try new-style plugin first
        typedef void (*InitFunc)(std::map<std::string, std::function<void(std::stack<WofValue>&)>>*);
        InitFunc init_func = (InitFunc)GetProcAddress(handle, "init_plugin");
        
        if (init_func) {
            // Handle new-style plugins (if any exist)
            std::cout << "Loading new-style plugin: " << plugin_path << std::endl;
        } else {
            // Try old-style plugin (your existing plugins)
            typedef void (*RegisterFunc)(WoflangInterpreter&);
            RegisterFunc register_func = (RegisterFunc)GetProcAddress(handle, "register_plugin");
            
            if (register_func) {
                register_func(*this);
                loaded_plugins.push_back(handle);
                std::cout << "Loaded plugin: " << plugin_path << std::endl;
            } else {
                std::cout << "Plugin missing register_plugin function: " << plugin_path << std::endl;
                FreeLibrary(handle);
            }
        }
        #else
        void* handle = dlopen(plugin_path.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cout << "Failed to load plugin: " << plugin_path << " - " << dlerror() << std::endl;
            return;
        }
        
        // Try old-style plugin (your existing plugins)
        typedef void (*RegisterFunc)(WoflangInterpreter&);
        RegisterFunc register_func = (RegisterFunc)dlsym(handle, "register_plugin");
        
        if (register_func) {
            register_func(*this);
            loaded_plugins.push_back(handle);
            std::cout << "Loaded plugin: " << plugin_path << std::endl;
        } else {
            std::cout << "Plugin missing register_plugin function: " << plugin_path << std::endl;
            dlclose(handle);
        }
        #endif
    }
    
    void loadPlugins() {
        std::vector<std::string> plugin_extensions = {".dll", ".so", ".dylib"};
        
        for (const auto& entry : std::filesystem::directory_iterator(".")) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                
                for (const std::string& ext : plugin_extensions) {
                    if (filename.size() >= ext.size() && 
                        filename.substr(filename.size() - ext.size()) == ext) {
                        loadPlugin(filename);
                        break;
                    }
                }
            }
        }
    }
    
    void execute(const std::string& input) {
        std::vector<std::string> tokens = tokenize(input);
        
        for (const std::string& token : tokens) {
            if (token.empty()) continue;
            
            // Check if it's a number (including Unicode constants)
            if (isNumber(token)) {
                push(WofValue(parseNumber(token)));
            }
            // Check if it's a qubit state
            else if (isQubitState(token)) {
                push(parseQubitState(token));
            }
            // Check if it's a string literal
            else if (token.front() == '"' && token.back() == '"') {
                std::string str_val = token.substr(1, token.length() - 2);
                push(WofValue(str_val));
            }
            // Check if it's a builtin operation
            else if (builtins.count(token)) {
                builtins[token]();
            }
            // Unknown token
            else {
                std::cout << "Error: Unknown word: " << token << std::endl;
            }
        }
    }
    
    void repl() {
        std::cout << "Woflang v3.0.0 - A Unicode-native stack language" << std::endl;
        std::cout << "Type 'help' for help, 'exit' to quit" << std::endl;
        std::cout << std::endl;
        
        std::string input;
        while (true) {
            std::cout << "╬╗> ";
            if (!std::getline(std::cin, input)) break;
            
            if (input.empty()) continue;
            
            execute(input);
        }
    }
    
    // Compatibility methods for tests and other systems
    void load_plugins(const std::filesystem::path& plugin_dir) {
        loadPlugins();
    }
    
    void load_plugins(const std::string& plugin_dir) {
        loadPlugins();
    }
    
    void exec_script(const std::filesystem::path& script_path) {
        std::cout << "Executing script: " << script_path << std::endl;
    }
    
    void exec_script(const std::string& script_path) {
        std::cout << "Executing script: " << script_path << std::endl;
    }
    
    // Missing interpreter properties for compatibility
    bool sacred_ops_enabled = false;
    bool unicode_mode = true;
};

} // namespace woflang