// command_dictionary.cpp
#include "woflang_config.h"
#include "constants.h"
#include "command_dictionary.h"
#include <fstream>
#include <sstream>
#include <iostream>

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

CommandDictionary& CommandDictionary::getInstance() {
    static CommandDictionary instance;
    return instance;
}

bool CommandDictionary::loadFromFile(const std::string& filename) {
    if (!Utils::fileExists(filename)) {
        errorSystem.reportError(ERR_STRING_NULL_PTR, "Dictionary file not found");
        return false;
    }
    
    try {
        std::string content = Utils::readFileContents(filename);
        // Process dictionary content...
    } catch (const std::exception& e) {
        errorSystem.reportError(ERR_STRING_NULL_PTR, e.what());
        return false;
    }
}

    auto& errorSystem = ErrorSystem::getInstance();
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        errorSystem.reportError(ERR_STRING_NULL_PTR, "Failed to open dictionary file: " + filename);
        return false;
    }

    std::string line;
    int lineNumber = 0;
    bool success = true;

    while (std::getline(file, line)) {
        lineNumber++;
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#' || line[0] == ';') {
            continue;
        }

        DictionaryEntry entry;
        if (!parseDictionaryLine(line, entry)) {
            errorSystem.reportError(ERR_STRING_INVALID_OP, 
                "Invalid dictionary entry at line " + std::to_string(lineNumber));
            success = false;
            continue;
        }

        if (!validateEntry(entry)) {
            errorSystem.reportError(ERR_TYPE_MISMATCH, 
                "Invalid command mapping at line " + std::to_string(lineNumber));
            success = false;
            continue;
        }

        mappings[entry.unicode] = entry;
    }

    file.close();
    return success;
}

bool CommandDictionary::saveToFile(const std::string& filename) const {
    auto& errorSystem = ErrorSystem::getInstance();
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        errorSystem.reportError(ERR_STRING_NULL_PTR, "Failed to open file for writing: " + filename);
        return false;
    }

    // Write header
    file << "# WoflangCPP Command Dictionary\n";
    file << "# Format: Unicode_Symbol Command_Name Description\n\n";

    for (const auto& [unicode, entry] : mappings) {
        file << entry.unicode << "\t" << entry.commandName;
        if (!entry.description.empty()) {
            file << "\t# " << entry.description;
        }
        file << "\n";
    }

    file.close();
    return true;
}

bool CommandDictionary::addMapping(const std::string& unicode, const std::string& commandName) {
    auto& errorSystem = ErrorSystem::getInstance();
    
    DictionaryEntry entry{unicode, commandName, ""};
    if (!validateEntry(entry)) {
        errorSystem.reportError(ERR_TYPE_MISMATCH, "Invalid command mapping");
        return false;
    }

    mappings[unicode] = entry;
    return true;
}

std::string CommandDictionary::getCommandName(const std::string& unicode) const {
    auto it = mappings.find(unicode);
    return (it != mappings.end()) ? it->second.commandName : "";
}

bool CommandDictionary::hasSymbol(const std::string& unicode) const {
    return mappings.find(unicode) != mappings.end();
}

bool CommandDictionary::parseDictionaryLine(const std::string& line, DictionaryEntry& entry) {
    std::istringstream iss(line);
    std::string unicode, commandName;
    
    if (!(iss >> unicode >> commandName)) {
        return false;
    }

    entry.unicode = unicode;
    entry.commandName = commandName;

    // Check for optional description (after #)
    std::string remaining;
    if (std::getline(iss, remaining)) {
        size_t commentPos = remaining.find('#');
        if (commentPos != std::string::npos) {
            entry.description = remaining.substr(commentPos + 1);
            // Trim leading/trailing whitespace from description
            while (!entry.description.empty() && std::isspace(entry.description.front())) {
                entry.description.erase(0, 1);
            }
            while (!entry.description.empty() && std::isspace(entry.description.back())) {
                entry.description.pop_back();
            }
        }
    }

    return true;
}

bool CommandDictionary::validateEntry(const DictionaryEntry& entry) {
    auto& errorSystem = ErrorSystem::getInstance();
    
    // Check Unicode symbol validity
    if (!errorSystem.checkUnicodeValid(entry.unicode)) {
        return false;
    }

    // Check command name validity (basic check)
    if (entry.commandName.empty() || entry.commandName.length() > 50) {
        errorSystem.reportError(ERR_STRING_INVALID_OP, "Invalid command name length");
        return false;
    }

    // Check command name format (alphanumeric and underscores only)
    if (!std::all_of(entry.commandName.begin(), entry.commandName.end(), 
                     [](char c) { return std::isalnum(c) || c == '_'; })) {
        errorSystem.reportError(ERR_STRING_INVALID_OP, "Invalid characters in command name");
        return false;
    }

    return true;
}

} // namespace woflang