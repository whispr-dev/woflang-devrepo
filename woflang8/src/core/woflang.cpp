#include "woflang.hpp"
#include "../io/tokenizer.hpp"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace woflang {

WoflangInterpreter::WoflangInterpreter() {
    // Register built-in ops and eggs
    register_op("cursed", [](std::stack<WofValue>& stack) {
        std::cout << "You have invoked the ancient Woflang curse! 👻\n";
    });
    register_op("egg", [](std::stack<WofValue>& stack) {
        std::cout << "🥚 You found the Woflang Easter Egg!\n";
    });
}

void WoflangInterpreter::register_op(const std::string& name, OpHandler handler) {
    op_table_[name] = handler;
}

void WoflangInterpreter::execute_line(const std::string& code) {
    auto tokens = tokenize(code);
    if (tokens.empty()) return;
    auto it = op_table_.find(tokens[0]);
    if (it != op_table_.end()) {
        std::stack<WofValue> stack; // For demonstration; expand for full language
        it->second(stack);
    } else {
        std::cout << "Unknown op: " << tokens[0] << "\n";
    }
}

void WoflangInterpreter::loadPlugin(const std::string& path) {
#ifdef _WIN32
    HMODULE handle = LoadLibraryA(path.c_str());
    if (!handle) return;
    using InitFunc = void(*)(OpTable*);
    auto init_func = reinterpret_cast<InitFunc>(GetProcAddress(handle, "init_plugin"));
    if (init_func) init_func(&op_table_);
#else
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) return;
    using InitFunc = void(*)(OpTable*);
    auto init_func = reinterpret_cast<InitFunc>(dlsym(handle, "init_plugin"));
    if (init_func) init_func(&op_table_);
#endif
}

void WoflangInterpreter::load_plugins(const std::filesystem::path& plugin_dir) {
    for (auto& entry : std::filesystem::directory_iterator(plugin_dir)) {
        if (entry.is_regular_file()) {
            loadPlugin(entry.path().string());
        }
    }
}

}
