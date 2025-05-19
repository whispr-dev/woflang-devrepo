#include "woflang.hpp"

#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>

// --- Main Interpreter ---

WoflangInterpreter::WoflangInterpreter() {
    // Register built-in ops (can be expanded)
    register_op("print", [](WoflangInterpreter& interp) {
        if (!interp.stack.empty()) {
            const auto& v = interp.stack.back();
            switch (v.type) {
            case WofType::Integer: std::cout << std::get<int64_t>(v.value); break;
            case WofType::Double: std::cout << std::get<double>(v.value); break;
            case WofType::String: std::cout << std::get<std::string>(v.value); break;
            case WofType::Symbol: std::cout << std::get<std::string>(v.value); break;
            case WofType::Unit: std::cout << "[unit]"; break;
            }
            if (v.unit) std::cout << " " << *v.unit;
            std::cout << std::endl;
        }
    });

    register_op("clear", [](WoflangInterpreter& interp) { interp.clear_stack(); });

    // Example math op
    register_op("+", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) throw std::runtime_error("Stack underflow on +");
        auto b = interp.stack.back(); interp.stack.pop_back();
        auto a = interp.stack.back(); interp.stack.pop_back();

        if (a.type == WofType::Integer && b.type == WofType::Integer)
            interp.stack.emplace_back(std::get<int64_t>(a.value) + std::get<int64_t>(b.value));
        else if (a.type == WofType::Double && b.type == WofType::Double)
            interp.stack.emplace_back(std::get<double>(a.value) + std::get<double>(b.value));
        else
            throw std::runtime_error("Type error in +");
    });

    // Example stack swap
    register_op("swap", [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) throw std::runtime_error("Stack underflow on swap");
        std::swap(interp.stack[interp.stack.size() - 1], interp.stack[interp.stack.size() - 2]);
    });
}

void WoflangInterpreter::register_op(const std::string& name, WofOpHandler handler) {
    op_handlers[name] = handler;
}

void WoflangInterpreter::load_plugin(const std::filesystem::path& dll_path) {
    HMODULE hPlugin = LoadLibraryW(dll_path.wstring().c_str());
    if (!hPlugin) throw std::runtime_error("Failed to load plugin: " + dll_path.string());

    auto reg_func = (RegisterPluginFunc)GetProcAddress(hPlugin, "register_plugin");
    if (!reg_func) {
        FreeLibrary(hPlugin);
        throw std::runtime_error("Plugin missing required 'register_plugin' function: " + dll_path.string());
    }
    reg_func(*this);
    plugin_handles.push_back(hPlugin);
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
        if (v.unit) std::cout << *v.unit;
        if (i + 1 != stack.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

void WoflangInterpreter::clear_stack() {
    stack.clear();
}

WoflangInterpreter::~WoflangInterpreter() {
    for (auto h : plugin_handles) {
        FreeLibrary(h);
    }
}

// --- Tokenization/Parsing ---

std::vector<std::string> WoflangInterpreter::tokenize(const std::string& line) {
    // Simple split on whitespace and keep quoted strings
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void WoflangInterpreter::dispatch_token(const std::string& token) {
    // Try op first
    auto it = op_handlers.find(token);
    if (it != op_handlers.end()) {
        it->second(*this);
        return;
    }

    // Integer literal?
    try {
        size_t idx;
        int64_t val = std::stoll(token, &idx, 10);
        if (idx == token.size()) {
            stack.emplace_back(val);
            return;
        }
    } catch (...) {}

    // Double literal?
    try {
        size_t idx;
        double val = std::stod(token, &idx);
        if (idx == token.size()) {
            stack.emplace_back(val);
            return;
        }
    } catch (...) {}

    // Otherwise treat as string/symbol
    stack.emplace_back(token, WofType::Symbol);
}

void WoflangInterpreter::error(const std::string& msg) {
    std::cerr << msg << std::endl;
}

