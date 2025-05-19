// src/core/woflang.hpp
#pragma once

#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <stdexcept>
#include <filesystem>
#include "WofValue.hpp"

namespace woflang {
    class WoflangInterpreter {
    public:
        // Constructor/destructor
        WoflangInterpreter();
        ~WoflangInterpreter();
        
        // Stack operations
        void push(const WofValue& value);
        WofValue pop();
        
        // Error handling
        void error(const std::string& message);
        
        // Token processing
        std::vector<std::string> tokenize(const std::string& line);
        void dispatch_token(const std::string& token);
        
        // Script execution
        void execute(const std::string& code);
        void exec_script(const std::filesystem::path& path);
        
        // Plugin loading
        void load_plugins(const std::filesystem::path& plugin_dir);
        
        // REPL
        void repl();
        
        // Public member variables
        std::vector<WofValue> stack;
        std::unordered_map<std::string, std::function<void(WoflangInterpreter&)>> op_handlers;
    };
}