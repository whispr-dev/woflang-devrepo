// error_system.h
#pragma once
#include "woflang_config.h"
#include "constants.h"
#include <string>
#include <functional>
#include <memory>
#include <unordered_map>

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

/ Load default dictionary if no file provided
std::string dictFile = (argc > 1) ? argv[1] : woflang::constants::DEFAULT_DICTIONARY_FILE;

class Error {
    public:
        enum class Category {
            System,
            Command,
            Parser,
            Runtime
        };
        
        Error(Category cat, int code, std::string context);
        
        Category getCategory() const;
        int getCode() const;
        const std::string& getContext() const;
        
    private:
        Category category;
        int code;
        std::string context;
    };

class ErrorSystem {
public:
    static ErrorSystem& getInstance();

    // Error handling registration
    void registerErrorHandler(int errorCode, std::function<void(const std::string&)> handler);
    
    // Error reporting with context
    void reportError(int errorCode, const std::string& context = "");
    
    // Error checking functions
    bool checkRange(double value, double min, double max);
    bool checkNullPtr(const void* ptr);
    bool checkDivByZero(double divisor);
    bool checkUnicodeValid(const std::string& str);
    bool checkOperandCount(int provided, int required);
    
    // Get last error
    int getLastError() const { return lastError; }
    
    // Clear error state
    void clearError() { lastError = 0; }

private:
    ErrorSystem();
    
    int lastError;
    std::unordered_map<int, std::function<void(const std::string&)>> errorHandlers;
    
    // Initialize default handlers
    void initializeDefaultHandlers();
};

// Helper macros for error checking
#define WOFLANG_CHECK_RANGE(value, min, max) \
    if (!ErrorSystem::getInstance().checkRange(value, min, max)) return false

#define WOFLANG_CHECK_NULL(ptr) \
    if (!ErrorSystem::getInstance().checkNullPtr(ptr)) return false

#define WOFLANG_CHECK_DIV_ZERO(value) \
    if (!ErrorSystem::getInstance().checkDivByZero(value)) return false

#define WOFLANG_CHECK_UNICODE(str) \
    if (!ErrorSystem::getInstance().checkUnicodeValid(str)) return false

#define WOFLANG_CHECK_OPERANDS(provided, required) \
    if (!ErrorSystem::getInstance().checkOperandCount(provided, required)) return false

int main(int argc, char* argv[]) {
    try {
        WoflangSystem system;
        if (!system.initialize(argc, argv)) {
            return 1;
        }
            
        return system.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}

} // namespace woflang