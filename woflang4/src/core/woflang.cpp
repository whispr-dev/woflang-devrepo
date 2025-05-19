// src/core/woflang.cpp
#include "woflang.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace woflang {

WoflangInterpreter::WoflangInterpreter() {
    // Register basic operations
    op_handlers["+"] = [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: + requires two arguments");
            return;
        }
        
        WofValue b = interp.pop();
        WofValue a = interp.pop();
        
        if (a.type == WofType::Integer && b.type == WofType::Integer) {
            interp.push(WofValue(std::get<int64_t>(a.value) + std::get<int64_t>(b.value)));
        } else if (a.type == WofType::Double || b.type == WofType::Double) {
            double a_val = (a.type == WofType::Integer) ? 
                std::get<int64_t>(a.value) : std::get<double>(a.value);
            double b_val = (b.type == WofType::Integer) ? 
                std::get<int64_t>(b.value) : std::get<double>(b.value);
            interp.push(WofValue(a_val + b_val));
        } else {
            interp.error("Type error: + requires numeric arguments");
        }
    };
    
    op_handlers["-"] = [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: - requires two arguments");
            return;
        }
        
        WofValue b = interp.pop();
        WofValue a = interp.pop();
        
        if (a.type == WofType::Integer && b.type == WofType::Integer) {
            interp.push(WofValue(std::get<int64_t>(a.value) - std::get<int64_t>(b.value)));
        } else if (a.type == WofType::Double || b.type == WofType::Double) {
            double a_val = (a.type == WofType::Integer) ? 
                std::get<int64_t>(a.value) : std::get<double>(a.value);
            double b_val = (b.type == WofType::Integer) ? 
                std::get<int64_t>(b.value) : std::get<double>(b.value);
            interp.push(WofValue(a_val - b_val));
        } else {
            interp.error("Type error: - requires numeric arguments");
        }
    };
    
    op_handlers["*"] = [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: * requires two arguments");
            return;
        }
        
        WofValue b = interp.pop();
        WofValue a = interp.pop();
        
        if (a.type == WofType::Integer && b.type == WofType::Integer) {
            interp.push(WofValue(std::get<int64_t>(a.value) * std::get<int64_t>(b.value)));
        } else if (a.type == WofType::Double || b.type == WofType::Double) {
            double a_val = (a.type == WofType::Integer) ? 
                std::get<int64_t>(a.value) : std::get<double>(a.value);
            double b_val = (b.type == WofType::Integer) ? 
                std::get<int64_t>(b.value) : std::get<double>(b.value);
            interp.push(WofValue(a_val * b_val));
        } else {
            interp.error("Type error: * requires numeric arguments");
        }
    };
    
    op_handlers["/"] = [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: / requires two arguments");
            return;
        }
        
        WofValue b = interp.pop();
        WofValue a = interp.pop();
        
        double b_val = (b.type == WofType::Integer) ? 
            std::get<int64_t>(b.value) : std::get<double>(b.value);
            
        if (b_val == 0.0) {
            interp.error("Division by zero");
            return;
        }
        
        if (a.type == WofType::Integer && b.type == WofType::Integer && 
            std::get<int64_t>(a.value) % std::get<int64_t>(b.value) == 0) {
            // Integer division with no remainder
            interp.push(WofValue(std::get<int64_t>(a.value) / std::get<int64_t>(b.value)));
        } else {
            // Use floating point division
            double a_val = (a.type == WofType::Integer) ? 
                std::get<int64_t>(a.value) : std::get<double>(a.value);
            interp.push(WofValue(a_val / b_val));
        }
    };
    
    op_handlers["print"] = [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            interp.error("Stack underflow: print requires at least one argument");
            return;
        }
        
        WofValue v = interp.pop();
        std::cout << v.to_string() << std::endl;
    };
    
    op_handlers["dup"] = [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            interp.error("Stack underflow: dup requires at least one argument");
            return;
        }
        
        interp.stack.push_back(interp.stack.back());
    };
    
    op_handlers["drop"] = [](WoflangInterpreter& interp) {
        if (interp.stack.empty()) {
            interp.error("Stack underflow: drop requires at least one argument");
            return;
        }
        
        interp.stack.pop_back();
    };
    
    op_handlers["swap"] = [](WoflangInterpreter& interp) {
        if (interp.stack.size() < 2) {
            interp.error("Stack underflow: swap requires at least two arguments");
            return;
        }
        
        std::swap(interp.stack[interp.stack.size() - 1], interp.stack[interp.stack.size() - 2]);
    };
}

WoflangInterpreter::~WoflangInterpreter() {
    // Clean up resources
}

void WoflangInterpreter::push(const WofValue& value) {
    stack.push_back(value);
}

WofValue WoflangInterpreter::pop() {
    if (stack.empty()) {
        error("Stack underflow");
    }
    
    WofValue v = stack.back();
    stack.pop_back();
    return v;
}

void WoflangInterpreter::error(const std::string& message) {
    throw std::runtime_error(message);
}

void WoflangInterpreter::execute(const std::string& code) {
    std::istringstream stream(code);
    std::string line;
    
    while (std::getline(stream, line)) {
        auto tokens = tokenize(line);
        for (const auto& token : tokens) {
            dispatch_token(token);
        }
    }
}

void WoflangInterpreter::exec_script(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file) {
        error("Failed to open file: " + path.string());
    }
    
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    execute(content);
}

void WoflangInterpreter::load_plugins(const std::filesystem::path& plugin_dir) {
    // Placeholder - we'll implement this later
    std::cout << "Loading plugins from: " << plugin_dir << std::endl;
    // TODO: Implement actual plugin loading
}

void WoflangInterpreter::repl() {
    std::cout << "WofLang REPL v3.0.0" << std::endl;
    std::cout << "Type 'exit' to quit" << std::endl;
    
    std::string line;
    while (true) {
        std::cout << ">> ";
        if (!std::getline(std::cin, line) || line == "exit") {
            break;
        }
        
        try {
            auto tokens = tokenize(line);
            for (const auto& token : tokens) {
                dispatch_token(token);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

} // namespace woflang