# unicode_validator.h
#include "woflang_config.h"
#include "constants.h"
#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <array>
#include <cstdint>

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

class UnicodeValidator {
    public:
    // Get singleton instance
    static UnicodeValidator& getInstance();

    // Main validation function for command symbols
    bool isValidCommandSymbol(const std::string& str) const;

    // Register valid Unicode ranges for commands
    void registerValidRange(uint32_t start, uint32_t end);

    // Add specific valid symbols
    void addValidSymbol(const std::string& symbol);

    bool loadDictionary(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            // Handle file opening error
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            // Skip empty lines and comments
            if (line.empty() || line[0] == '#') {
                continue;
            }

            // Split the line into symbol and command name
            std::istringstream iss(line);
            std::string symbol, commandName;
            if (iss >> symbol >> commandName) {
                // Register the symbol and command name
                registerSymbol(symbol);
            }
        }

        file.close();
        return true;
    }

    private:
    std::unordered_map<std::string, bool> validationCache;
    size_t maxCacheSize = 1000;
    
    void pruneCache() {
        if (validationCache.size() > maxCacheSize) {
            validationCache.clear();
        }
    }
};

private:
    UnicodeValidator();
    
    // Helper functions for UTF-8 validation
    bool isValidUTF8(const std::string& str) const;
    uint32_t convertToCodePoint(const std::string& str) const;
    bool isInValidRanges(uint32_t codePoint) const;
    
    // Storage for valid ranges and symbols
    struct Range {
        uint32_t start;
        uint32_t end;
    };
    std::vector<Range> validRanges;
    std::unordered_set<std::string> validSymbols;

    // Continuation byte checking
    bool isContinuationByte(uint8_t byte) const {
        return (byte & 0xC0) == 0x80;
    }
};

} // namespace woflang