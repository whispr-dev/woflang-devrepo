#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <memory>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <optional>
#include <windows.h> // Windows plugin loading

// Forward declare for plugin interface
class WoflangInterpreter;

// --- Token/Value Types ---
enum class WofType {
    Integer, Double, String, Symbol, Unit
};

// Token/value object for stack and variables
struct WofValue {
    WofType type;
    std::variant<int64_t, double, std::string> value;
    std::optional<std::string> unit; // e.g., "m", "s"

    WofValue(int64_t v) : type(WofType::Integer), value(v) {}
    WofValue(double v) : type(WofType::Double), value(v) {}
    WofValue(const std::string& v, WofType t = WofType::String) : type(t), value(v) {}
    WofValue(const char* v, WofType t = WofType::String) : type(t), value(std::string(v)) {}
    WofValue(int64_t v, const std::string& u) : type(WofType::Integer), value(v), unit(u) {}
    WofValue(double v, const std::string& u) : type(WofType::Double), value(v), unit(u) {}
};

// --- Opcode/Op Handler ---
using WofOpHandler = std::function<void(WoflangInterpreter&)>;

// --- Plugin Interface ---
struct WoflangPlugin {
    virtual ~WoflangPlugin() = default;
    virtual void register_ops(WoflangInterpreter&) = 0;
};

// The required exported function from each plugin DLL
using RegisterPluginFunc = void(*)(WoflangInterpreter&);

// --- Main Interpreter Class ---
class WoflangInterpreter {
public:
    WoflangInterpreter();

    // Stack
    std::vector<WofValue> stack;

    // Symbol table for user variables
    std::unordered_map<std::string, WofValue> symbols;

    // Opcode dispatcher
    std::unordered_map<std::string, WofOpHandler> op_handlers;

    // Plugin handles
    std::vector<HMODULE> plugin_handles;

    // API: Load plugins
    void load_plugin(const std::filesystem::path& dll_path);

    // API: Register opcodes
    void register_op(const std::string& name, WofOpHandler handler);

    // Parse a line/script and execute
    void exec_line(const std::string& line);
    void exec_script(const std::filesystem::path& filename);

    // REPL entry
    void repl();

    // Utility
    void print_stack() const;
    void clear_stack();

    // Destructor
    ~WoflangInterpreter();

private:
    // Internal parsing/tokenizer
    std::vector<std::string> tokenize(const std::string& line);
    void dispatch_token(const std::string& token);

    // Internal: error handler
    void error(const std::string& msg);
};

/**
 * @brief Stack-based Unicode/glyph interpreter for the woflang language.
 */
class WoflangInterpreter {
public:
    /**
     * @brief Create a new interpreter with empty stack and symbol table.
     */
    WoflangInterpreter();

    /// Data stack for values.
    std::vector<WofValue> stack;

    /// Symbol table for user variables.
    std::unordered_map<std::string, WofValue> symbols;

    /// Opcode dispatcher table.
    std::unordered_map<std::string, WofOpHandler> op_handlers;

    /// Loaded plugin handles (Windows DLLs).
    std::vector<HMODULE> plugin_handles;

    /**
     * @brief Dynamically load a plugin DLL and register its ops.
     * @param dll_path Filesystem path to the plugin DLL.
     */
    void load_plugin(const std::filesystem::path& dll_path);

    /**
     * @brief Register a named opcode handler.
     */
    void register_op(const std::string& name, WofOpHandler handler);

    /**
     * @brief Parse and execute a single line of code.
     */
    void exec_line(const std::string& line);

    /**
     * @brief Parse and execute an entire script file.
     */
    void exec_script(const std::filesystem::path& filename);

    /**
     * @brief Run the REPL loop on stdin.
     */
    void repl();

    /**
     * @brief Print the stack contents.
     */
    void print_stack() const;

    /**
     * @brief Clear the stack.
     */
    void clear_stack();

    /// Destructor, unloads all plugins.
    ~WoflangInterpreter();

private:
    std::vector<std::string> tokenize(const std::string& line);
    void dispatch_token(const std::string& token);

    void error(const std::string& msg);
};
