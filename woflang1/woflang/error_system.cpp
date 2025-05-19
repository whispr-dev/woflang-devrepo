// error_system.cpp
#include "woflang_config.h"
#include "constants.h"
#include "error_system.h"
#include "err_chk.h"
#include <iostream>
#include <cmath>

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

ErrorSystem::ErrorSystem() : lastError(0) {
    initializeDefaultHandlers();
}

ErrorSystem& ErrorSystem::getInstance() {
    static ErrorSystem instance;
    return instance;
}

void ErrorSystem::initializeDefaultHandlers() {
    // Register handlers for all error codes from err_chk.h
    registerErrorHandler(ERR_HEADER_MISSING, [](const std::string& ctx) {
        std::cerr << "Header missing error" << (ctx.empty() ? "" : ": " + ctx) << std::endl;
    });

    registerErrorHandler(ERR_BLOCK_ORDER, [](const std::string& ctx) {
        std::cerr << "Block order error" << (ctx.empty() ? "" : ": " + ctx) << std::endl;
    });

    registerErrorHandler(ERR_UNRECOGNIZED, [](const std::string& ctx) {
        std::cerr << "Unrecognized command error" << (ctx.empty() ? "" : ": " + ctx) << std::endl;
    });

    registerErrorHandler(ERR_TYPE_MISMATCH, [](const std::string& ctx) {
        std::cerr << "Type mismatch error" << (ctx.empty() ? "" : ": " + ctx) << std::endl;
    });

    // Add more handlers for your other error codes...
}

void ErrorSystem::registerErrorHandler(int errorCode, std::function<void(const std::string&)> handler) {
    errorHandlers[errorCode] = std::move(handler);
}

void ErrorSystem::reportError(int errorCode, const std::string& context) {
    lastError = errorCode;
    
    auto it = errorHandlers.find(errorCode);
    if (it != errorHandlers.end()) {
        it->second(context);
    } else {
        std::cerr << "Unknown error " << errorCode << (context.empty() ? "" : ": " + context) << std::endl;
    }
}

bool ErrorSystem::checkRange(double value, double min, double max) {
    if (std::isnan(value) || value < min || value > max) {
        reportError(ERR_OUT_OF_BOUNDS, "Value " + std::to_string(value) + " out of range [" + 
                   std::to_string(min) + ", " + std::to_string(max) + "]");
        return false;
    }
    return true;
}

bool ErrorSystem::checkNullPtr(const void* ptr) {
    if (ptr == nullptr) {
        reportError(ERR_RUNTIME_NULL_PTR, "Null pointer detected");
        return false;
    }
    return true;
}

bool ErrorSystem::checkDivByZero(double divisor) {
    if (std::abs(divisor) < 1e-10) {  // Using small epsilon for floating-point comparison
        reportError(ERR_RUNTIME_DIV_ZERO, "Division by zero");
        return false;
    }
    return true;
}

bool ErrorSystem::checkUnicodeValid(const std::string& str) {
    if (str.empty()) {
        reportError(ERR_STRING_NULL_PTR, "Empty Unicode string");
        return false;
    }
    // Add more Unicode validation using your UnicodeValidator
    return true;
}

bool ErrorSystem::checkOperandCount(int provided, int required) {
    if (provided < required) {
        reportError(ERR_TYPE_MISMATCH, 
                   "Insufficient operands. Required: " + std::to_string(required) + 
                   ", Provided: " + std::to_string(provided));
        return false;
    }
    return true;
}

} // namespace woflang