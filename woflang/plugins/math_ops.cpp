/**
 * @file woflang.hpp
 * @brief Main header file for Woflang language
 */

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <variant>
#include <stdexcept>
#include <optional>
#include <iostream>
#include <filesystem>
#include <cmath>
#include <algorithm>
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
 * @brief Enumeration of value types in Woflang
 */
enum class WofType {
    Integer,  ///< 64-bit signed integer
    Double,   ///< Double-precision floating point
    String,   ///< UTF-8 string
    Symbol    ///< Symbol (identifier)
};

/**
 * @brief Value type in Woflang
 */
class WofValue {
public:
    /// Type of this value
    WofType type;
    
    /// Actual value (variant)
    std::variant<int64_t, double, std::string> value;
    
    /// Optional unit (e.g., "m" for meters)
    std::optional<std::string> unit;
    
    /// Default constructor (integer zero)
    WofValue() : type(WofType::Integer), value(0LL) {}
    
    /// Integer constructor
    explicit WofValue(int64_t i) : type(WofType::Integer), value(i) {}
    
    /// Double constructor
    explicit WofValue(double d) : type(WofType::Double), value(d) {}
    
    /// String constructor
    explicit WofValue(const std::string& s, WofType t = WofType::String) : 
        type(t), value(s) {}
    
    /// String with move constructor
    explicit WofValue(std::string&& s, WofType t = WofType::String) : 
        type(t), value(std::move(s)) {}
    
    /// Copy constructor
    WofValue(const WofValue& other) = default;
    
    /// Move constructor
    WofValue(WofValue&& other) noexcept = default;
    
    /// Copy assignment
    WofValue& operator=(const WofValue& other) = default;
    
    /// Move assignment
    WofValue& operator=(WofValue&& other) noexcept = default;
    
    /// Equality operator
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
    WoflangInterpreter() {
        register_core_ops();
    }
    
    /// Destructor (unloads plugins)
    ~WoflangInterpreter() {
        // Unload plugins
#ifdef WOFLANG_PLATFORM_WINDOWS
        for (auto handle : plugin_handles) {
            FreeLibrary(handle);
        }
#else
        for (auto handle : plugin_handles) {
            dlclose(handle);
        }
#endif
    }
    
    /// The data stack
    std::vector<WofValue> stack;
    
    /// Map of operation names to handlers
    std::unordered_map<std::string, WofOpHandler> op_handlers;
    
    /// Register an operation
    void register_op(const std::string& name, WofOpHandler handler) {
        op_handlers[name] = std::move(handler);
    }
    
    /// Load a plugin from a DLL/SO file
    void load_plugin(const std::filesystem::path& dll_path) {
        if (!std::filesystem::exists(dll_path)) {
            std::cerr << "Plugin file not found: " << dll_path << std::endl;
            return;
        }
        
#ifdef WOFLANG_PLATFORM_WINDOWS
        // Load the DLL
        HMODULE handle = LoadLibraryW(dll_path.wstring().c_str());
        if (!handle) {
            std::cerr << "Failed to load plugin: " << dll_path << std::endl;
            return;
        }
        
        // Get the register_plugin function
        auto register_plugin = reinterpret_cast<RegisterPluginFunc>(
            GetProcAddress(handle, "register_plugin"));
        
        if (!register_plugin) {
            std::cerr << "Plugin is missing register_plugin function: " << dll_path << std::endl;
            FreeLibrary(handle);
            return;
        }
        
        // Register the plugin
        register_plugin(*this);
        
        // Store the handle for cleanup
        plugin_handles.push_back(handle);
#else
        // Load the shared object
        void* handle = dlopen(dll_path.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "Failed to load plugin: " << dll_path << " - " << dlerror() << std::endl;
            return;
        }
        
        // Clear any existing error
        dlerror();
        
        // Get the register_plugin function
        auto register_plugin = reinterpret_cast<RegisterPluginFunc>(
            dlsym(handle, "register_plugin"));
        
        const char* error = dlerror();
        if (error) {
            std::cerr << "Plugin is missing register_plugin function: " << dll_path << " - " << error << std::endl;
            dlclose(handle);
            return;
        }
        
        // Register the plugin
        register_plugin(*this);
        
        // Store the handle for cleanup
        plugin_handles.push_back(handle);
#endif
        
        std::cout << "Loaded plugin: " << dll_path.filename() << std::endl;
    }
    
    /// Load all plugins from a directory
    void load_plugins(const std::filesystem::path& plugin_dir) {
        if (!std::filesystem::exists(plugin_dir) || !std::filesystem::is_directory(plugin_dir)) {
            std::cerr << "Plugin directory not found: " << plugin_dir << std::endl;
            return;
        }
        
        // Iterate over all files in the directory
        for (const auto& entry : std::filesystem::directory_iterator(plugin_dir)) {
            if (!entry.is_regular_file()) {
                continue;
            }
            
            // Check the file extension
            auto path = entry.path();
            auto ext = path.extension().string();
            
#ifdef WOFLANG_PLATFORM_WINDOWS
            if (ext == ".dll") {
                load_plugin(path);
            }
#else
            if (ext == ".so") {
                load_plugin(path);
            }
#endif
        }
    }
    
    /// Execute a line of code
    void exec_line(const std::string& line) {
        auto tokens = tokenize(line);
        
        for (const auto& token : tokens) {
            try {
                dispatch_token(token);
            } catch (const std::exception& e) {
                error(e.what());
            }
        }
    }
    
    /// Execute a script file
    void exec_script(const std::filesystem::path& filename) {
        if (!std::filesystem::exists(filename)) {
            error("Script file not found: " + filename.string());
            return;
        }
        
        try {
            std::ifstream file(filename);
            if (!file.is_open()) {
                error("Failed to open script file: " + filename.string());
                return;
            }
            
            std::string line;
            while (std::getline(file, line)) {
                exec_line(line);
            }
        } catch (const std::exception& e) {
            error("Script error: " + std::string(e.what()));
        }
    }
    
    /// Start the REPL (Read-Eval-Print Loop)
    void repl() {
        std::cout << "Woflang Interpreter" << std::endl;
        std::cout << "Type 'exit' to quit" << std::endl;
        
        std::string line;
        
        while (true) {
            std::cout << "wof> ";
            std::getline(std::cin, line);
            
            if (line == "exit" || line == "quit") {
                break;
            }
            
            try {
                exec_line(line);
            } catch (const std::exception& e) {
                error(e.what());
            }
        }
    }
    
    /// Print the current stack to stdout
    void print_stack() const {
        std::cout << "Stack [" << stack.size() << "]: ";
        
        for (const auto& v : stack) {
            std::cout << v.to_string() << " ";
        }
        
        std::cout << std::endl;
    }
    
    /// Clear the stack
    void clear_stack() {
        stack.clear();
    }
    
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
    void error(const std::string& msg) {
        std::cerr << "Error: " << msg << std::endl;
    }
    
private:
    /// Register core operations
    void register_core_ops() {
        // ----- Basic Stack Operations -----
        
        // dup: Duplicate the top stack value
        register_op("dup", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on dup");
            }
            
            interp.stack.push_back(interp.stack.back());
        });
        
        // drop: Drop the top stack value
        register_op("drop", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on drop");
            }
            
            interp.stack.pop_back();
        });
        
        // swap: Swap the top two stack values
        register_op("swap", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on swap");
            }
            
            std::swap(interp.stack[interp.stack.size() - 1], interp.stack[interp.stack.size() - 2]);
        });
        
        // over: Duplicate the second stack value to the top
        register_op("over", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on over");
            }
            
            interp.stack.push_back(interp.stack[interp.stack.size() - 2]);
        });
        
        // rot: Rotate the top three stack values
        register_op("rot", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 3) {
                throw std::runtime_error("Stack underflow on rot");
            }
            
            auto a = interp.stack[interp.stack.size() - 3];
            auto b = interp.stack[interp.stack.size() - 2];
            auto c = interp.stack[interp.stack.size() - 1];
            
            interp.stack[interp.stack.size() - 3] = b;
            interp.stack[interp.stack.size() - 2] = c;
            interp.stack[interp.stack.size() - 1] = a;
        });
        
        // ----- Arithmetic Operations -----
        
        // +: Add two values
        register_op("+", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on +");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer && b.type == WofType::Integer) {
                // Integer addition
                interp.stack.emplace_back(std::get<int64_t>(a.value) + std::get<int64_t>(b.value));
            } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                       (b.type == WofType::Integer || b.type == WofType::Double)) {
                // Mixed or double addition
                double val_a = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                double val_b = b.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
                
                interp.stack.emplace_back(val_a + val_b);
            } else if ((a.type == WofType::String || a.type == WofType::Symbol) && 
                       (b.type == WofType::String || b.type == WofType::Symbol)) {
                // String concatenation
                std::string val_a = std::get<std::string>(a.value);
                std::string val_b = std::get<std::string>(b.value);
                
                if (a.type == WofType::String) {
                    // Remove the closing quote
                    val_a = val_a.substr(0, val_a.size() - 1);
                }
                
                if (b.type == WofType::String) {
                    // Remove the opening quote
                    val_b = val_b.substr(1);
                }
                
                interp.stack.emplace_back(val_a + val_b, a.type);
            } else {
                throw std::runtime_error("Type error: + requires matching numeric or string types");
            }
        });
        
        // -: Subtract two values
        register_op("-", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on -");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer && b.type == WofType::Integer) {
                // Integer subtraction
                interp.stack.emplace_back(std::get<int64_t>(a.value) - std::get<int64_t>(b.value));
            } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                       (b.type == WofType::Integer || b.type == WofType::Double)) {
                // Mixed or double subtraction
                double val_a = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                double val_b = b.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
                
                interp.stack.emplace_back(val_a - val_b);
            } else {
                throw std::runtime_error("Type error: - requires numeric values");
            }
        });
        
        // *: Multiply two values
        register_op("*", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on *");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if (a.type == WofType::Integer && b.type == WofType::Integer) {
                // Integer multiplication
                interp.stack.emplace_back(std::get<int64_t>(a.value) * std::get<int64_t>(b.value));
            } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                       (b.type == WofType::Integer || b.type == WofType::Double)) {
                // Mixed or double multiplication
                double val_a = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                double val_b = b.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
                
                interp.stack.emplace_back(val_a * val_b);
            } else {
                throw std::runtime_error("Type error: * requires numeric values");
            }
        });
        
        // /: Divide two values
        register_op("/", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on /");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Check for division by zero
            if ((b.type == WofType::Integer && std::get<int64_t>(b.value) == 0) ||
                (b.type == WofType::Double && std::get<double>(b.value) == 0.0)) {
                throw std::runtime_error("Division by zero");
            }
            
            if (a.type == WofType::Integer && b.type == WofType::Integer) {
                // Integer division (floating point result)
                interp.stack.emplace_back(static_cast<double>(std::get<int64_t>(a.value)) / 
                                         static_cast<double>(std::get<int64_t>(b.value)));
            } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                       (b.type == WofType::Integer || b.type == WofType::Double)) {
                // Mixed or double division
                double val_a = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                double val_b = b.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
                
                interp.stack.emplace_back(val_a / val_b);
            } else {
                throw std::runtime_error("Type error: / requires numeric values");
            }
        });
        
        // mod: Modulo operation
        register_op("mod", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on mod");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Check for modulo by zero
            if ((b.type == WofType::Integer && std::get<int64_t>(b.value) == 0) ||
                (b.type == WofType::Double && std::get<double>(b.value) == 0.0)) {
                throw std::runtime_error("Modulo by zero");
            }
            
            if (a.type == WofType::Integer && b.type == WofType::Integer) {
                // Integer modulo
                interp.stack.emplace_back(std::get<int64_t>(a.value) % std::get<int64_t>(b.value));
            } else if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                       (b.type == WofType::Integer || b.type == WofType::Double)) {
                // Mixed or double modulo (using fmod)
                double val_a = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                double val_b = b.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
                
                interp.stack.emplace_back(std::fmod(val_a, val_b));
            } else {
                throw std::runtime_error("Type error: mod requires numeric values");
            }
        });
        
        // idiv: Integer division
        register_op("idiv", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on idiv");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            // Check for division by zero
            if ((b.type == WofType::Integer && std::get<int64_t>(b.value) == 0) ||
                (b.type == WofType::Double && std::get<double>(b.value) == 0.0)) {
                throw std::runtime_error("Division by zero");
            }
            
            if (a.type == WofType::Integer && b.type == WofType::Integer) {
                // Integer division (integer result)
                interp.stack.emplace_back(std::get<int64_t>(a.value) / std::get<int64_t>(b.value));
            } else {
                throw std::runtime_error("Type error: idiv requires integer values");
            }
        });
        
        // pow: Power operation
        register_op("pow", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("Stack underflow on pow");
            }
            
            auto b = interp.stack.back(); interp.stack.pop_back();
            auto a = interp.stack.back(); interp.stack.pop_back();
            
            if ((a.type == WofType::Integer || a.type == WofType::Double) && 
                (b.type == WofType::Integer || b.type == WofType::Double)) {
                // Convert to doubles for pow
                double val_a = a.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(a.value)) : std::get<double>(a.value);
                double val_b = b.type == WofType::Integer ? 
                    static_cast<double>(std::get<int64_t>(b.value)) : std::get<double>(b.value);
                
                // Calculate power
                double result = std::pow(val_a, val_b);
                
                // Check if the result can be represented as an integer
                if (b.type == WofType::Integer && std::get<int64_t>(b.value) >= 0 &&
                    result == std::floor(result) && 
                    result <= static_cast<double>(std::numeric_limits<int64_t>::max()) &&
                    result >= static_cast<double>(std::numeric_limits<int64_t>::min())) {
                    // Integer power with integer result
                    interp.stack.emplace_back(static_cast<int64_t>(result));
                } else {
                    // Double result
                    interp.stack.emplace_back(result);
                }
            } else {
                throw std::runtime_error("Type error: pow requires numeric values");
            }
        });
        
        // sqrt: Square root
        register_op("sqrt", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_