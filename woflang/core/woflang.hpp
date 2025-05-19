/**
 * @file woflang.hpp
 * @brief Main header file for Woflang
 * 
 * This file provides the core types and classes for the Woflang stack-based
 * programming language.
 */

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdexcept>
#include <optional>
#include <random>
#include <chrono>
#include <complex>

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
#   define WOFLANG_PLATFORM_WINDOWS
#   include <windows.h>
#else
#   define WOFLANG_PLATFORM_UNIX
#   include <dlfcn.h>
#endif

namespace woflang {

/**
 * @brief Value types supported by Woflang
 */
enum class WofType {
    Integer,    ///< 64-bit signed integer
    Double,     ///< Double-precision floating point
    String,     ///< String (quoted text)
    Symbol      ///< Symbol (unquoted identifier)
};

/**
 * @brief Main value class for Woflang
 * 
 * This class represents values on the stack and in the language.
 */
class WofValue {
public:
    /// The type of this value
    WofType type;
    
    /// The actual value stored as a variant
    std::variant<int64_t, double, std::string> value;
    
    /// Optional unit for the value (e.g., "m" for meters)
    std::optional<std::string> unit;
    
    /// Constructor for integer values
    explicit WofValue(int64_t i) : type(WofType::Integer), value(i) {}
    
    /// Constructor for double values
    explicit WofValue(double d) : type(WofType::Double), value(d) {}
    
    /// Constructor for string/symbol values
    explicit WofValue(const std::string& s, WofType t = WofType::String) 
        : type(t), value(s) {}
    
    /// Default constructor (used internally)
    WofValue() : type(WofType::Integer), value(0LL) {}
    
    /// Copy constructor
    WofValue(const WofValue&) = default;
    
    /// Move constructor
    WofValue(WofValue&&) = default;
    
    /// Copy assignment
    WofValue& operator=(const WofValue&) = default;
    
    /// Move assignment
    WofValue& operator=(WofValue&&) = default;
    
    // Missing beginning of code 3.cpp (equality operator implementation)
    bool operator==(const WofValue& other) const {
        if (type != other.type || unit != other.unit) {
            return false;
        }
        
        switch (type) {
            case WofType::Integer:
                return std::get<int64_t>(value) == std::get<int64_t>(other.value);
            case WofType::Double:
                return std::get<double>(value) == std::get<double>(other.value);
            case WofType::String:
            case WofType::Symbol:
                return std::get<std::string>(value) == std::get<std::string>(other.value);
            default:
                return false;
        }
    }    
};    
    /// Inequality operator
    bool operator!=(const WofValue& other) const {
        return !(*this == other);
    }
    
    /// Conversion to string for display
    [[nodiscard]] std::string to_string() const {
        std::string result;
        
        switch (type) {
            case WofType::Integer:
                result = std::to_string(std::get<int64_t>(value));
                break;
            case WofType::Double: {
                result = std::to_string(std::get<double>(value));
                // Remove trailing zeros
                if (result.find('.') != std::string::npos) {
                    result = result.substr(0, result.find_last_not_of('0') + 1);
                    if (result.back() == '.') {
                        result.pop_back();
                    }
                }
                break;
            }
            case WofType::String:
                result = "\"" + std::get<std::string>(value) + "\"";
                break;
            case WofType::Symbol:
                result = std::get<std::string>(value);
                break;
        }
        
        if (unit) {
            result += " " + *unit;
        }
        
        return result;
    }
    
    /// Get numeric value (throws if not numeric)
    [[nodiscard]] double as_numeric() const {
        if (type == WofType::Integer) {
            return static_cast<double>(std::get<int64_t>(value));
        } else if (type == WofType::Double) {
            return std::get<double>(value);
        } else {
            throw std::runtime_error("Value is not numeric");
        }
    }
    
    /// Check if value is numeric (integer or double)
    [[nodiscard]] bool is_numeric() const {
        return type == WofType::Integer || type == WofType::Double;
    }
};

// Forward declaration of interpreter class
class WoflangInterpreter;

/**
 * @brief Function type for operation handlers
 */
using WofOpHandler = std::function<void(WoflangInterpreter&)>;

/**
 * @brief Function type for plugin registration
 */
using RegisterPluginFunc = void (*)(WoflangInterpreter&);

/**
 * @brief Interface for Woflang plugins
 */
class WoflangPlugin {
public:
    /// Virtual destructor
    virtual ~WoflangPlugin() = default;
    
    /// Register operations with the interpreter
    virtual void register_ops(WoflangInterpreter&) = 0;
};

/**
 * @brief Main interpreter class for Woflang
 */
class WoflangInterpreter {
public:
    /// Constructor
    WoflangInterpreter();
    
    /// Destructor (unloads plugins)
    ~WoflangInterpreter();
    
    /// The data stack
    std::vector<WofValue> stack;
    
    /// Map of operation names to handlers
    std::unordered_map<std::string, WofOpHandler> op_handlers;
    
    /// Register an operation
    void register_op(const std::string& name, WofOpHandler handler);
    
    /// Load a plugin from a DLL/SO file
    void load_plugin(const std::filesystem::path& dll_path);
    
    /// Load all plugins from a directory
    void load_plugins(const std::filesystem::path& plugin_dir);
    
    /// Execute a line of code
    void exec_line(const std::string& line);
    
    /// Execute a script file
    void exec_script(const std::filesystem::path& filename);
    
    /// Start the REPL (Read-Eval-Print Loop)
    void repl();
    
    /// Print the current stack to stdout
    void print_stack() const;
    
    /// Clear the stack
    void clear_stack();
    
    /// Push a value onto the stack
    template<typename T>
    void push(T&& value) {
        stack.push_back(std::forward<T>(value));
    }
    
    /// Pop a value from the stack (throws if stack is empty)
    WofValue pop() {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow");
        }
        WofValue v = stack.back();
        stack.pop_back();
        return v;
    }
    
    /// Pop an integer from the stack (throws if not an integer)
    int64_t pop_int() {
        WofValue v = pop();
        if (v.type != WofType::Integer) {
            throw std::runtime_error("Expected integer");
        }
        return std::get<int64_t>(v.value);
    }
    
    /// Pop a double from the stack (throws if not a double)
    double pop_double() {
        WofValue v = pop();
        if (v.type != WofType::Double) {
            throw std::runtime_error("Expected double");
        }
        return std::get<double>(v.value);
    }
    
    /// Pop a numeric value (integer or double) as a double
    double pop_numeric() {
        WofValue v = pop();
        if (v.type == WofType::Integer) {
            return static_cast<double>(std::get<int64_t>(v.value));
        } else if (v.type == WofType::Double) {
            return std::get<double>(v.value);
        } else {
            throw std::runtime_error("Expected numeric value");
        }
    }
    
    /// Pop a string from the stack (throws if not a string)
    std::string pop_string() {
        WofValue v = pop();
        if (v.type != WofType::String) {
            throw std::runtime_error("Expected string");
        }
        return std::get<std::string>(v.value);
    }
    
    /// Pop a symbol from the stack (throws if not a symbol)
    std::string pop_symbol() {
        WofValue v = pop();
        if (v.type != WofType::Symbol) {
            throw std::runtime_error("Expected symbol");
        }
        return std::get<std::string>(v.value);
    }
    
    /// Pop a boolean value (0=false, non-0=true)
    bool pop_bool() {
        WofValue v = pop();
        if (v.type == WofType::Integer) {
            return std::get<int64_t>(v.value) != 0;
        } else if (v.type == WofType::Double) {
            return std::get<double>(v.value) != 0.0;
        } else {
            throw std::runtime_error("Expected boolean value");
        }
    }
    
    /// Check if the stack has at least n elements
    [[nodiscard]] bool stack_has(size_t n) const {
        return stack.size() >= n;
    }
    
    /// Report an error
    void error(const std::string& msg);
    
private:
    /// Tokenize a line of code into tokens
    std::vector<std::string> tokenize(const std::string& line);
    
    /// Dispatch a token (execute an op or push a value)
    void dispatch_token(const std::string& token);
    
    /// Plugin handles for cleanup
#ifdef WOFLANG_PLATFORM_WINDOWS
    std::vector<HMODULE> plugin_handles;
#else
    std::vector<void*> plugin_handles;
#endif
};

// Export macro for plugins
#if defined(WOFLANG_PLATFORM_WINDOWS)
#   define WOFLANG_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
#   define WOFLANG_PLUGIN_EXPORT extern "C" __attribute__((visibility("default")))
#endif

// Convenience macro for registering operations
#define REGISTER_OP(interp, name, lambda) \
    (interp).register_op((name), (lambda))

} // namespace woflang





















