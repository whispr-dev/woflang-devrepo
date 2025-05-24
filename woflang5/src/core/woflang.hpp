// woflang.hpp - Core header for Woflang
#pragma once

#include <string>
#include <vector>
#include <map>
#include <variant>
#include <optional>
#include <functional>
#include <iostream>
#include <memory>
#include <filesystem>

namespace woflang {

// Unified type system for Woflang values
enum class WofType {
    Nil,
    Boolean,
    Integer,
    Double,
    String,
    Symbol,
    // Special types
    Qubit,      // For quantum states
    Complex,    // For complex numbers
    List,       // For collections
    Function    // For stored functions/lambdas
};

// Forward declarations
class WoflangInterpreter;

// Core value type that can hold any Woflang value
struct WofValue {
    using ValueType = std::variant<
        std::monostate,                    // Nil
        bool,                              // Boolean
        int64_t,                           // Integer
        double,                            // Double
        std::string,                       // String/Symbol
        std::complex<double>,              // Complex
        std::vector<WofValue>,             // List
        std::function<void(WoflangInterpreter&)>  // Function
    >;
    
    WofType type;
    ValueType value;
    std::optional<std::string> unit;  // Optional unit for physical quantities
    
    // Constructors
    WofValue() : type(WofType::Nil), value(std::monostate{}) {}
    WofValue(bool v) : type(WofType::Boolean), value(v) {}
    WofValue(int v) : type(WofType::Integer), value(static_cast<int64_t>(v)) {}
    WofValue(int64_t v) : type(WofType::Integer), value(v) {}
    WofValue(double v) : type(WofType::Double), value(v) {}
    WofValue(const std::string& v, WofType t = WofType::String) : type(t), value(v) {}
    WofValue(const char* v) : type(WofType::String), value(std::string(v)) {}
    WofValue(const std::complex<double>& v) : type(WofType::Complex), value(v) {}
    WofValue(const std::vector<WofValue>& v) : type(WofType::List), value(v) {}
    WofValue(std::function<void(WoflangInterpreter&)> v) : type(WofType::Function), value(v) {}
    
    // Constructor with unit
    WofValue(int64_t v, const std::string& u) : type(WofType::Integer), value(v), unit(u) {}
    WofValue(double v, const std::string& u) : type(WofType::Double), value(v), unit(u) {}
    
    // Helper methods
    bool is_numeric() const {
        return type == WofType::Integer || type == WofType::Double || type == WofType::Complex;
    }
    
    double as_numeric() const {
        switch (type) {
            case WofType::Integer: return static_cast<double>(std::get<int64_t>(value));
            case WofType::Double: return std::get<double>(value);
            case WofType::Complex: return std::abs(std::get<std::complex<double>>(value));
            default: return 0.0;
        }
    }
    
    std::string to_string() const;
};

// Operation handler type
using WofOpHandler = std::function<void(WoflangInterpreter&)>;

// Plugin interface
class WoflangPlugin {
public:
    virtual ~WoflangPlugin() = default;
    virtual void register_ops(WoflangInterpreter& interp) = 0;
};

// Main interpreter class
class WoflangInterpreter {
public:
    WoflangInterpreter();
    ~WoflangInterpreter();
    
    // Core data
    std::vector<WofValue> stack;
    std::map<std::string, WofOpHandler> op_handlers;
    std::map<std::string, WofValue> variables;
    
    // Configuration
    bool sacred_ops_enabled = true;
    bool unicode_mode = true;
    
    // Core operations
    void register_op(const std::string& name, WofOpHandler handler);
    void push(const WofValue& value);
    WofValue pop();
    WofValue peek() const;
    
    // Execution
    void execute(const std::string& code);
    void exec_line(const std::string& line);
    void exec_script(const std::filesystem::path& path);
    void dispatch_token(const std::string& token);
    
    // Plugin management
    void load_plugin(const std::filesystem::path& path);
    void load_plugins(const std::filesystem::path& plugin_dir);
    
    // REPL
    void repl();
    
    // Stack operations
    void print_stack() const;
    void clear_stack();
    
    // Error handling
    void error(const std::string& message);
    
    // Tokenization
    std::vector<std::string> tokenize(const std::string& line);
    
private:
    // Plugin handles
    std::vector<std::shared_ptr<void>> plugin_handles;
    
    // Register built-in operations
    void register_builtins();
};

// Platform-specific plugin export macro
#ifdef _WIN32
    #define WOFLANG_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
    #define WOFLANG_PLUGIN_EXPORT extern "C" __attribute__((visibility("default")))
#endif

} // namespace woflang