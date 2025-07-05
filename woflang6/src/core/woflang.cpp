// woflang.cpp - Core implementation
#include "woflang.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <random>
#include <chrono>
#include <codecvt>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace woflang {

// Convert WofValue to string for display
std::string WofValue::to_string() const {
    switch (type) {
        case WofType::Nil:
            return "nil";
        case WofType::Boolean:
            return std::get<bool>(value) ? "true" : "false";
        case WofType::Integer:
            return std::to_string(std::get<int64_t>(value));
        case WofType::Double:
            return std::to_string(std::get<double>(value));
        case WofType::String:
        case WofType::Symbol:
            return std::get<std::string>(value);
        case WofType::Complex: {
            auto c = std::get<std::complex<double>>(value);
            std::stringstream ss;
            ss << c.real() << "+" << c.imag() << "i";
            return ss.str();
        }
        case WofType::List: {
            std::stringstream ss;
            ss << "[";
            auto& list = std::get<std::vector<WofValue>>(value);
            for (size_t i = 0; i < list.size(); ++i) {
                if (i > 0) ss << ", ";
                ss << list[i].to_string();
            }
            ss << "]";
            return ss.str();
        }
        case WofType::Function:
            return "<function>";
        default:
            return "<unknown>";
    }
}

// Constructor
WoflangInterpreter::WoflangInterpreter() {
    register_builtins();
}

// Destructor - clean up plugins
WoflangInterpreter::~WoflangInterpreter() {
    plugin_handles.clear();
}

// Register built-in operations
void WoflangInterpreter::register_builtins() {
    // Basic arithmetic
    register_op("+", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: + requires two arguments");
            return;
        }
        
        auto b = interp.pop();
        auto a = interp.pop();
        
        if (a.type == WofType::Integer && b.type == WofType::Integer) {
            interp.push(WofValue(std::get<int64_t>(a.value) + std::get<int64_t>(b.value)));
        } else if (a.is_numeric() && b.is_numeric()) {
            interp.push(WofValue(a.as_numeric() + b.as_numeric()));
        } else if (a.type == WofType::String && b.type == WofType::String) {
            interp.push(WofValue(std::get<std::string>(a.value) + std::get<std::string>(b.value)));
        } else {
            interp.error("Type error: + requires matching types");
        }
    });
    
    register_op("-", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: - requires two arguments");
            return;
        }
        
        auto b = interp.pop();
        auto a = interp.pop();
        
        if (a.type == WofType::Integer && b.type == WofType::Integer) {
            interp.push(WofValue(std::get<int64_t>(a.value) - std::get<int64_t>(b.value)));
        } else if (a.is_numeric() && b.is_numeric()) {
            interp.push(WofValue(a.as_numeric() - b.as_numeric()));
        } else {
            interp.error("Type error: - requires numeric arguments");
        }
    });
    
    register_op("*", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: * requires two arguments");
            return;
        }
        
        auto b = interp.pop();
        auto a = interp.pop();
        
        if (a.type == WofType::Integer && b.type == WofType::Integer) {
            interp.push(WofValue(std::get<int64_t>(a.value) * std::get<int64_t>(b.value)));
        } else if (a.is_numeric() && b.is_numeric()) {
            interp.push(WofValue(a.as_numeric() * b.as_numeric()));
        } else {
            interp.error("Type error: * requires numeric arguments");
        }
    });
    
    register_op("/", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: / requires two arguments");
            return;
        }
        
        auto b = interp.pop();
        auto a = interp.pop();
        
        if (b.as_numeric() == 0.0) {
            // Special handling for sacred ops
            if (interp.sacred_ops_enabled) {
                std::cout << "⚠️  Attempting division by zero... ";
                std::cout << "The void gazes back. Stack consumed by infinity.\n";
                interp.clear_stack();
                interp.push(WofValue(std::numeric_limits<double>::infinity()));
                return;
            } else {
                interp.error("Division by zero");
                return;
            }
        }
        
        interp.push(WofValue(a.as_numeric() / b.as_numeric()));
    });
    
    // Stack operations
    register_op("dup", [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            interp.error("Stack underflow: dup requires at least one value");
            return;
        }
        interp.push(interp.peek());
    });
    
    register_op("drop", [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            interp.error("Stack underflow: drop requires at least one value");
            return;
        }
        interp.pop();
    });
    
    register_op("swap", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: swap requires at least two values");
            return;
        }
        std::swap(interp.stack[interp.stack.size() - 1], 
                  interp.stack[interp.stack.size() - 2]);
    });
    
    register_op("over", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: over requires at least two values");
            return;
        }
        interp.push(interp.stack[interp.stack.size() - 2]);
    });
    
    register_op("rot", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 3) {
            interp.error("Stack underflow: rot requires at least three values");
            return;
        }
        auto c = interp.pop();
        auto b = interp.pop();
        auto a = interp.pop();
        interp.push(b);
        interp.push(c);
        interp.push(a);
    });
    
    // I/O operations
    register_op("print", [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            interp.error("Stack underflow: print requires at least one value");
            return;
        }
        auto v = interp.pop();
        std::cout << v.to_string();
        if (v.unit) {
            std::cout << " " << *v.unit;
        }
        std::cout << std::endl;
    });
    
    register_op(".", [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            interp.error("Stack underflow: . requires at least one value");
            return;
        }
        auto v = interp.pop();
        std::cout << v.to_string();
        if (v.unit) {
            std::cout << " " << *v.unit;
        }
        std::cout << " ";
    });
    
    register_op(".s", [](WoflangInterpreter& interp) {
        interp.print_stack();
    });
    
    register_op("cr", [](WoflangInterpreter& interp) {
        std::cout << std::endl;
    });
    
    // Comparison operations
    register_op("=", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: = requires two values");
            return;
        }
        auto b = interp.pop();
        auto a = interp.pop();
        
        bool equal = false;
        if (a.type == b.type) {
            if (a.type == WofType::Integer) {
                equal = std::get<int64_t>(a.value) == std::get<int64_t>(b.value);
            } else if (a.type == WofType::Double) {
                equal = std::abs(std::get<double>(a.value) - std::get<double>(b.value)) < 1e-10;
            } else if (a.type == WofType::String || a.type == WofType::Symbol) {
                equal = std::get<std::string>(a.value) == std::get<std::string>(b.value);
            }
        }
        interp.push(WofValue(equal));
    });
    
    register_op("<", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: < requires two values");
            return;
        }
        auto b = interp.pop();
        auto a = interp.pop();
        interp.push(WofValue(a.as_numeric() < b.as_numeric()));
    });
    
    register_op(">", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: > requires two values");
            return;
        }
        auto b = interp.pop();
        auto a = interp.pop();
        interp.push(WofValue(a.as_numeric() > b.as_numeric()));
    });
    
    // Control flow
    register_op("if", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 3) {
            interp.error("Stack underflow: if requires condition and two values");
            return;
        }
        auto else_val = interp.pop();
        auto then_val = interp.pop();
        auto cond = interp.pop();
        
        bool condition = false;
        if (cond.type == WofType::Boolean) {
            condition = std::get<bool>(cond.value);
        } else if (cond.type == WofType::Integer) {
            condition = std::get<int64_t>(cond.value) != 0;
        }
        
        if (condition) {
            if (then_val.type == WofType::Function) {
                std::get<std::function<void(WoflangInterpreter&)>>(then_val.value)(interp);
            } else {
                interp.push(then_val);
            }
        } else {
            if (else_val.type == WofType::Function) {
                std::get<std::function<void(WoflangInterpreter&)>>(else_val.value)(interp);
            } else {
                interp.push(else_val);
            }
        }
    });
    
    // Special/Sacred operations
    register_op("∞", [](WoflangInterpreter& interp) {
        interp.push(WofValue(std::numeric_limits<double>::infinity()));
    });
    
    register_op("∅", [](WoflangInterpreter& interp) {
        std::cout << "The void consumes all. Stack cleared.\n";
        interp.clear_stack();
    });
    
    register_op("chaos", [](WoflangInterpreter& interp) {
        static std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        interp.push(WofValue(dis(gen)));
        std::cout << "From chaos, order emerges...\n";
    });
}

// Core operations
void WoflangInterpreter::register_op(const std::string& name, WofOpHandler handler) {
    op_handlers[name] = handler;
}

void WoflangInterpreter::push(const WofValue& value) {
    stack.push_back(value);
}

WofValue WoflangInterpreter::pop() {
    if (stack.empty()) {
        error("Stack underflow");
        return WofValue();
    }
    WofValue v = stack.back();
    stack.pop_back();
    return v;
}

WofValue WoflangInterpreter::peek() const {
    if (stack.empty()) {
        throw std::runtime_error("Stack underflow");
    }
    return stack.back();
}

// Tokenization - handles Unicode properly
std::vector<std::string> WoflangInterpreter::tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::string current_token;
    bool in_string = false;
    
    // Convert to UTF-32 for proper Unicode handling
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    std::u32string u32line = conv.from_bytes(line);
    
    for (char32_t ch : u32line) {
        if (in_string) {
            current_token += conv.to_bytes(ch);
            if (ch == U'"') {
                tokens.push_back(current_token);
                current_token.clear();
                in_string = false;
            }
        } else {
            if (ch == U'"') {
                if (!current_token.empty()) {
                    tokens.push_back(current_token);
                    current_token.clear();
                }
                current_token += '"';
                in_string = true;
            } else if (std::isspace(ch)) {
                if (!current_token.empty()) {
                    tokens.push_back(current_token);
                    current_token.clear();
                }
            } else {
                current_token += conv.to_bytes(ch);
            }
        }
    }
    
    if (!current_token.empty()) {
        tokens.push_back(current_token);
    }
    
    return tokens;
}

void WoflangInterpreter::dispatch_token(const std::string& token) {
    // Check if it's an operation
    if (op_handlers.find(token) != op_handlers.end()) {
        op_handlers[token](*this);
        return;
    }
    
    // Try to parse as number
    try {
        // Integer
        size_t idx;
        int64_t ival = std::stoll(token, &idx);
        if (idx == token.length()) {
            push(WofValue(ival));
            return;
        }
    } catch (...) {}
    
    try {
        // Double
        size_t idx;
        double dval = std::stod(token, &idx);
        if (idx == token.length()) {
            push(WofValue(dval));
            return;
        }
    } catch (...) {}
    
    // String literal
    if (token.length() >= 2 && token[0] == '"' && token[token.length() - 1] == '"') {
        push(WofValue(token.substr(1, token.length() - 2)));
        return;
    }
    
    // Check for special constants
    if (token == "true") {
        push(WofValue(true));
        return;
    }
    if (token == "false") {
        push(WofValue(false));
        return;
    }
    if (token == "nil") {
        push(WofValue());
        return;
    }
    
    // Check for variable reference
    if (token[0] == '$' && token.length() > 1) {
        std::string var_name = token.substr(1);
        if (variables.find(var_name) != variables.end()) {
            push(variables[var_name]);
            return;
        } else {
            error("Undefined variable: " + var_name);
            return;
        }
    }
    
    // Check for variable assignment
    if (token[0] == '!' && token.length() > 1) {
        std::string var_name = token.substr(1);
        if (!stack.empty()) {
            variables[var_name] = pop();
            return;
        } else {
            error("Stack underflow: cannot assign to " + var_name);
            return;
        }
    }
    
    // Otherwise, treat as symbol
    push(WofValue(token, WofType::Symbol));
}

void WoflangInterpreter::execute(const std::string& code) {
    std::istringstream stream(code);
    std::string line;
    
    while (std::getline(stream, line)) {
        exec_line(line);
    }
}

void WoflangInterpreter::exec_line(const std::string& line) {
    // Skip empty lines and comments
    if (line.empty() || line[0] == '#') return;
    
    auto tokens = tokenize(line);
    for (const auto& token : tokens) {
        try {
            dispatch_token(token);
        } catch (const std::exception& e) {
            error(e.what());
        }
    }
}

void WoflangInterpreter::exec_script(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file) {
        error("Cannot open script: " + path.string());
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        exec_line(line);
    }
}

// Plugin management
void WoflangInterpreter::load_plugin(const std::filesystem::path& path) {
#ifdef _WIN32
    HMODULE handle = LoadLibraryW(path.wstring().c_str());
    if (!handle) {
        error("Failed to load plugin: " + path.string());
        return;
    }
    
    auto register_func = (void(*)(WoflangInterpreter&))GetProcAddress(handle, "register_plugin");
    if (!register_func) {
        FreeLibrary(handle);
        error("Plugin missing register_plugin function: " + path.string());
        return;
    }
    
    // Store handle to prevent unloading
    plugin_handles.push_back(std::shared_ptr<void>(handle, FreeLibrary));
#else
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        error("Failed to load plugin: " + path.string() + " (" + dlerror() + ")");
        return;
    }
    
    auto register_func = (void(*)(WoflangInterpreter&))dlsym(handle, "register_plugin");
    if (!register_func) {
        dlclose(handle);
        error("Plugin missing register_plugin function: " + path.string());
        return;
    }
    
    plugin_handles.push_back(std::shared_ptr<void>(handle, dlclose));
#endif
    
    // Register the plugin
    register_func(*this);
    std::cout << "Loaded plugin: " << path.filename().string() << std::endl;
}

void WoflangInterpreter::load_plugins(const std::filesystem::path& plugin_dir) {
    if (!std::filesystem::exists(plugin_dir)) {
        std::cout << "Plugin directory does not exist: " << plugin_dir << std::endl;
        return;
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(plugin_dir)) {
        if (!entry.is_regular_file()) continue;
        
        const auto& path = entry.path();
#ifdef _WIN32
        if (path.extension() == ".dll") {
#else
        if (path.extension() == ".so" || path.extension() == ".dylib") {
#endif
            try {
                load_plugin(path);
            } catch (const std::exception& e) {
                std::cerr << "Failed to load plugin " << path << ": " << e.what() << std::endl;
            }
        }
    }
}

// REPL
void WoflangInterpreter::repl() {
    std::cout << "Woflang v3.0.0 - A Unicode-native stack language\n";
    std::cout << "Type 'help' for help, 'exit' to quit\n\n";
    
    std::string line;
    while (true) {
        std::cout << "λ> ";
        if (!std::getline(std::cin, line)) break;
        
        if (line == "exit" || line == "quit") break;
        
        if (line == "help") {
            std::cout << "\nWoflang Commands:\n";
            std::cout << "  Basic ops: + - * / dup drop swap over rot\n";
            std::cout << "  I/O: print . .s cr\n";
            std::cout << "  Comparison: = < >\n";
            std::cout << "  Special: ∞ ∅ chaos\n";
            std::cout << "  Variables: !name (store), $name (fetch)\n";
            std::cout << "  System: help exit clear\n";
            std::cout << "\nPlugins provide additional operations.\n\n";
            continue;
        }
        
        if (line == "clear") {
            clear_stack();
            std::cout << "Stack cleared.\n";
            continue;
        }
        
        exec_line(line);
    }
}

void WoflangInterpreter::print_stack() const {
    std::cout << "Stack [" << stack.size() << "]: ";
    for (const auto& v : stack) {
        std::cout << v.to_string();
        if (v.unit) {
            std::cout << " " << *v.unit;
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}

void WoflangInterpreter::clear_stack() {
    stack.clear();
}

void WoflangInterpreter::error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
}

} // namespace woflang