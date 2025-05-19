// command_dictionary.h
#pragma once
#include "woflang_config.h"
#include "constants.h"
#include <string>
#include <unordered_map>
#include <functional>
#include "error_system.h"

namespace woflang {

// Get system instances
auto& cmdSystem = woflang::CommandSystem::getInstance();
auto& dict = woflang::CommandDictionary::getInstance();
auto& errorSystem = woflang::ErrorSystem::getInstance();

// Print version info
std::cout << "WoflangCPP v" 
          << woflang::VERSION.major << "."
          << woflang::VERSION.minor << "."
          << woflang::VERSION.patch << std::endl;

// Load default dictionary if no file provided
std::string dictFile = (argc > 1) ? argv[1] : woflang::constants::DEFAULT_DICTIONARY_FILE;

class CommandDictionary {
public:
    static CommandDictionary& getInstance();

    bool registerPluginCommands(const std::string& pluginName,
                            const std::vector<CommandMapping>& commands) {
        for (const auto& cmd : commands) {
            if (!addMapping(cmd.unicode, pluginName + "::" + cmd.name)) {
                return false;
            }
        }
        return true;
    }
};

    // Load dictionary from file
    bool loadFromFile(const std::string& filename);
    
    // Save dictionary to file
    bool saveToFile(const std::string& filename) const;
    
    // Add mapping to dictionary
    bool addMapping(const std::string& unicode, const std::string& commandName);
    
    // Get command name for Unicode symbol
    std::string getCommandName(const std::string& unicode) const;
    
    // Check if symbol exists in dictionary
    bool hasSymbol(const std::string& unicode) const;
    
    // Format for dictionary file
    struct DictionaryEntry {
        std::string unicode;
        std::string commandName;
        std::string description;  // Optional description of what the command does
    };

private:
    CommandDictionary() = default;
    
    std::unordered_map<std::string, DictionaryEntry> mappings;
    
    // Helper functions
    bool parseDictionaryLine(const std::string& line, DictionaryEntry& entry);
    bool validateEntry(const DictionaryEntry& entry);
};

} // namespace woflang