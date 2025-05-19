// commands.h

#include "woflang_config.h"
#include "constants.h"
#pragma once
#include "parser.h"
#include "command_dictionary.h"
#include "error_system.h"
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <vector>
#include "unicode_validator.h"

namespace woflang {

// Get system instances
 auto& cmdSystem = woflang::CommandSystem::getInstance();
 auto& dict = woflang::CommandDictionary::getInstance();
 auto& errorSystem = woflang::ErrorSystem::getInstance();

/ Print version info
std::cout << "WoflangCPP v" 
          << woflang::VERSION.major << "."
          << woflang::VERSION.minor << "."
          << woflang::VERSION.patch << std::endl;

// Load default dictionary if no file provided
std::string dictFile = (argc > 1) ? argv[1] : woflang::constants::DEFAULT_DICTIONARY_FILE;

class CommandRegistry {
    public:
        template<typename T>
        bool registerCommand(const std::string& unicode, T&& cmd) {
            static_assert(std::is_invocable_v<T, double*, int>);
            return registerCommandImpl(unicode, std::forward<T>(cmd));
        }
        
        // Command validation
        bool validateCommand(const std::string& unicode) const;
        
    private:
        std::unordered_map<std::string, std::function<void(double*, int)>> commands;
        std::mutex registryMutex;
    };

class CommandSystem {
    public:
        virtual ~CommandSystem() = default;
        
        // Use RAII for command registration
        class CommandRegistration {
            CommandSystem& system;
            std::string unicode;
        public:
            CommandRegistration(CommandSystem& sys, const std::string& u, CommandFunction f);
            ~CommandRegistration();
        };
        
        // Simplified command execution
        bool executeCommand(const std::string& unicode, std::span<double> operands);
    };
            
            // Handle command results
            void setResult(double result) { lastResult = result; }
            double getLastResult() const { return lastResult; }
        
        private:
            CommandSystem();
            
            std::unordered_map<std::string, CommandFunction> commandMap;
            std::unique_ptr<Parser> parser;
            double lastResult;
            std::mutex commandMutex;;
            UnicodeValidator& unicodeValidator;
            std::function<void(int)> errorCallback;
            

            // Helper functions
            void registerBasicCommands();
            bool validateCommand(const std::string& unicode);
            void logCommand(const std::string& unicode, bool success);
            void handleError(int errorCode);
        };

} // namespace woflang