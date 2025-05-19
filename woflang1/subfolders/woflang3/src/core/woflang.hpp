#pragma once

#include <string>
#include <vector>
#include <functional>
#include <map>
#include <variant>
#include <iostream>
#include <random>
#include <stdexcept>

enum class WofType { Integer, Double, String };

struct WofValue {
    WofType type;
    std::variant<int64_t, double, std::string> value;

    WofValue(int64_t v) : type(WofType::Integer), value(v) {}
    WofValue(double v) : type(WofType::Double), value(v) {}
    WofValue(const std::string& v) : type(WofType::String), value(v) {}
};

class WoflangInterpreter {
public:
    std::vector<WofValue> stack;

    // Each op name -> handler lambda
    std::map<std::string, std::function<void(WoflangInterpreter&)>> op_handlers;

    // Register an op
    void register_op(const std::string& name, std::function<void(WoflangInterpreter&)> fn) {
        op_handlers[name] = fn;
    }

    // Clear stack
    void clear_stack() {
        stack.clear();
    }

    // Dispatch: run an op by name
    void dispatch_token(const std::string& token) {
        auto it = op_handlers.find(token);
        if (it != op_handlers.end())
            it->second(*this);
        else
            std::cerr << "Unknown operation: " << token << std::endl;
    }

    // Print stack contents
    void print_stack() const {
        std::cout << "Stack [";
        for (const auto& v : stack) {
            switch (v.type) {
            case WofType::Integer:
                std::cout << std::get<int64_t>(v.value) << " ";
                break;
            case WofType::Double:
                std::cout << std::get<double>(v.value) << " ";
                break;
            case WofType::String:
                std::cout << '"' << std::get<std::string>(v.value) << "\" ";
                break;
            }
        }
        std::cout << "]" << std::endl;
    }
};

// Plugin loader/export macro
#if defined(_WIN32) || defined(_WIN64)
#   define WOFLANG_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
#   define WOFLANG_PLUGIN_EXPORT extern "C"
#endif

