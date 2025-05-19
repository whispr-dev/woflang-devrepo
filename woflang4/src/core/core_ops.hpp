cpp#pragma once

#include <string>
#include <vector>
#include <functional>
#include <map>
#include <variant>
#include <iostream>
#include <random>
#include <stdexcept>
#include <filesystem>
#include <optional>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

enum class WofType { Integer, Double, String, Symbol };

struct WofValue {
    WofType type;
    std::variant<int64_t, double, std::string> value;
    std::optional<std::string> unit;

    // Constructors for all types
    WofValue(int64_t v) : type(WofType::Integer), value(v) {}
    WofValue(double v) : type(WofType::Double), value(v) {}
    WofValue(const std::string& v, WofType t = WofType::String) 
        : type(t), value(v) {}
    WofValue(int64_t v, const std::string& u) 
        : type(WofType::Integer), value(v), unit(u) {}
    WofValue(double v, const std::string& u) 
        : type(WofType::Double), value(v), unit(u) {}
};

// Function type for plugin registration
class WoflangInterpreter;
using WofOpHandler = std::function<void(WoflangInterpreter&)>;
using RegisterPluginFunc = void (*)(WoflangInterpreter&);

class WoflangInterpreter {
public:
    WoflangInterpreter();
    ~WoflangInterpreter();

    // Stack and operations
    std::vector<WofValue> stack;
    std::map<std::string, WofOpHandler> op_handlers;
    
    // Plugin and ops management
    void register_op(const std::string& name, WofOpHandler handler);
    void load_plugin(const std::filesystem::path& dll_path);
    void load_plugins(const std::filesystem::path& plugin_dir);
    
    // Execution
    void exec_line(const std::string& line);
    void exec_script(const std::filesystem::path& filename);
    void repl();
    
    // Stack inspection/manipulation
    void print_stack() const;
    void clear_stack();
    
    // Helper methods
    std::vector<std::string> tokenize(const std::string& line);
    void dispatch_token(const std::string& token);
    void error(const std::string& msg);
    
private:
    #ifdef _WIN32
    std::vector<HMODULE> plugin_handles;
    #else
    std::vector<void*> plugin_handles;
    #endif
};

// Plugin export macro
#if defined(_WIN32) || defined(_WIN64)
#   define WOFLANG_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
#   define WOFLANG_PLUGIN_EXPORT extern "C" __attribute__((visibility("default")))
#endif

WoflangInterpreter::WoflangInterpreter() {
    // Register built-in ops (moved to core_ops.hpp)
}

void WoflangInterpreter::register_op(const std::string& name, WofOpHandler handler) {
    op_handlers[name] = handler;
}

void WoflangInterpreter::load_plugin(const std::filesystem::path& dll_path) {
#ifdef _WIN32
    HMODULE hPlugin = LoadLibraryW(dll_path.wstring().c_str());
    if (!hPlugin) throw std::runtime_error("Failed to load plugin: " + dll_path.string());

    auto reg_func = (RegisterPluginFunc)GetProcAddress(hPlugin, "register_plugin");
    if (!reg_func) {
        FreeLibrary(hPlugin);
        throw std::runtime_error("Plugin missing required 'register_plugin' function: " + dll_path.string());
    }
    reg_func(*this);
    plugin_handles.push_back(hPlugin);
#else
    void* handle = dlopen(dll_path.c_str(), RTLD_LAZY);
    if (!handle) throw std::runtime_error("Failed to load plugin: " + dll_path.string() + " (" + dlerror() + ")");
    
    auto reg_func = (RegisterPluginFunc)dlsym(handle, "register_plugin");
    if (!reg_func) {
        dlclose(handle);
        throw std::runtime_error("Plugin missing required 'register_plugin' function: " + dll_path.string());
    }
    reg_func(*this);
    plugin_handles.push_back(handle);
#endif
}

void WoflangInterpreter::load_plugins(const std::filesystem::path& plugin_dir) {
    for (const auto& entry : std::filesystem::directory_iterator(plugin_dir)) {
#ifdef _WIN32
        if (entry.path().extension() == ".dll") {
#else
        if (entry.path().extension() == ".so" || entry.path().extension() == ".dylib") {
#endif
            try {
                load_plugin(entry.path());
                std::cout << "Loaded plugin: " << entry.path().filename().string() << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Plugin load failed: " << e.what() << std::endl;
            }
        }
    }
}

void WoflangInterpreter::exec_line(const std::string& line) {
    auto tokens = tokenize(line);
    for (const auto& token : tokens) {
        try {
            dispatch_token(token);
        } catch (const std::exception& e) {
            error(std::string("Error: ") + e.what());
        }
    }
}

void WoflangInterpreter::exec_script(const std::filesystem::path& filename) {
    std::ifstream fin(filename);
    if (!fin) throw std::runtime_error("Cannot open script: " + filename.string());
    std::string line;
    while (std::getline(fin, line)) {
        exec_line(line);
    }
}

void WoflangInterpreter::repl() {
    std::string line;
    std::cout << "woflang REPL (type 'exit' or Ctrl+C to quit)\n";
    while (true) {
        std::cout << ">> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "exit") break;
        exec_line(line);
        print_stack();
    }
}

void WoflangInterpreter::print_stack() const {
    std::cout << "Stack [";
    for (size_t i = 0; i < stack.size(); ++i) {
        const auto& v = stack[i];
        if (v.type == WofType::Integer)
            std::cout << std::get<int64_t>(v.value);
        else if (v.type == WofType::Double)
            std::cout << std::get<double>(v.value);
        else if (v.type == WofType::String || v.type == WofType::Symbol)
            std::cout << '"' << std::get<std::string>(v.value) << '"';
        if (v.unit) std::cout << " " << *v.unit;
        if (i + 1 != stack.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

void WoflangInterpreter::clear_stack() {
    stack.clear();
}

WoflangInterpreter::~WoflangInterpreter() {
    for (auto h : plugin_handles) {
#ifdef _WIN32
        FreeLibrary(h);
#else
        dlclose(h);
#endif
    }
}