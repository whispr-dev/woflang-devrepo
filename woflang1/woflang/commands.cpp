// commands.cpp
#include "woflang_config.h"
#include "constants.h"
#include "commands.h"
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

CommandSystem::CommandSystem() : lastResult(0.0) {}
    : unicodeValidator(UnicodeValidator::getInstance()) {
    // Set default error callback
    errorCallback = [](int code) {
        std::cerr << "Command error: " << code << std::endl;
    };
}

CommandSystem& CommandSystem::getInstance() {
    static CommandSystem instance;
    return instance;
}

bool CommandSystem::validateCommand(const std::string& unicode) {
    if (!unicodeValidator.isValidCommandSymbol(unicode)) {
        handleError(ERR_UNRECOGNIZED_COMMAND);
        return false;
    }
    return true;
}

bool CommandSystem::executeCommand(const std::string& unicode, double* operands, int numOperands) {
    // Check operands are in valid range
    for (int i = 0; i < numOperands; i++) {
        if (!Utils::isInRange(operands[i], -1e9, 1e9)) {  // Example range
            errorSystem.reportError(ERR_OUT_OF_BOUNDS);
            return false;
        }
    }
    // Rest of execute command code...
}

    if (!validateCommand(unicode)) {
        return false;
    }

    std::lock_guard<std::mutex> lock(commandMutex);
    if (commandMap.find(unicode) != commandMap.end()) {
        handleError(ERR_ATTRIBUTE); // Using your existing error code for duplicate command
        return false;
    }

    commandMap[unicode] = std::move(func);
    return true;
}

bool CommandSystem::executeCommand(const std::string& unicode, double* operands, int numOperands) {
    if (!validateCommand(unicode)) {
        return false;
    }

    std::lock_guard<std::mutex> lock(commandMutex);
    auto it = commandMap.find(unicode);
    if (it == commandMap.end()) {
        handleError(ERR_UNRECOGNIZED_COMMAND);
        return false;
    }

    try {
        it->second(operands, numOperands);
        logCommand(unicode, true);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error executing command " << unicode << ": " << e.what() << std::endl;
        handleError(ERR_RUNTIME);
        logCommand(unicode, false);
        return false;
    }
}

bool CommandSystem::loadDictionary(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        handleError(ERR_STRING_NULL_PTR); // Using existing error code for file error
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string unicode, funcName;
        if (!(iss >> unicode >> funcName)) {
            handleError(ERR_STRING_INVALID_OP);
            continue;
        }

        if (!validateCommand(unicode)) {
            continue;
        }

        // Command registration logic here
        // This is where you'd map the funcName to actual function pointers
        std::cout << "Loaded command mapping: " << unicode << " -> " << funcName << std::endl;
    }

    file.close();
    return true;
}

// In commands.cpp
bool CommandSystem::executeCommand(const std::string& unicode, double* operands, int numOperands) {
    auto& dict = CommandDictionary::getInstance();
    
    // First check if the symbol exists in our dictionary
    if (!dict.hasSymbol(unicode)) {
        handleError(ERR_UNRECOGNIZED_COMMAND);
        return false;
    }

    // Get the command name
    std::string cmdName = dict.getCommandName(unicode);
    
    // Look up the actual command function
    auto it = commandMap.find(cmdName);
    if (it == commandMap.end()) {
        handleError(ERR_UNRECOGNIZED_COMMAND);
        return false;
    }

    try {
        it->second(operands, numOperands);
        logCommand(unicode, true);
        return true;
    } catch (const std::exception& e) {
        handleError(ERR_RUNTIME);
        logCommand(unicode, false);
        return false;
    }
}

    auto& errorSystem = ErrorSystem::getInstance();
    
    // Check Unicode validity
    WOFLANG_CHECK_UNICODE(unicode);
    
    // Check operands
    WOFLANG_CHECK_NULL(operands);
    WOFLANG_CHECK_OPERANDS(numOperands, 2);  // Assuming command needs 2 operands
    
    std::lock_guard<std::mutex> lock(commandMutex);
    auto it = commandMap.find(unicode);
    if (it == commandMap.end()) {
        errorSystem.reportError(ERR_UNRECOGNIZED, "Unknown command: " + unicode);
        return false;
    }

    try {
        it->second(operands, numOperands);
        logCommand(unicode, true);
        return true;
    } catch (const std::exception& e) {
        errorSystem.reportError(ERR_RUNTIME, std::string("Command execution failed: ") + e.what());
        logCommand(unicode, false);
        return false;
    }
}

bool CommandSystem::initialize() {
    auto& dict = CommandDictionary::getInstance();
    parser = std::make_unique<Parser>(*this, dict);
    
    // Register all basic commands
    registerBasicCommands();
    
    return true;
}

void CommandSystem::registerBasicCommands() {
    // Basic arithmetic
    registerCommand("⊕", [](double* ops, int n) {
        if (n < 2) return;
        ops[0] = ops[0] + ops[1];
    });

    registerCommand("⊖", [](double* ops, int n) {
        if (n < 2) return;
        ops[0] = ops[0] - ops[1];
    });

    registerCommand("⊗", [](double* ops, int n) {
        if (n < 2) return;
        ops[0] = ops[0] * ops[1];
    });

    registerCommand("⊘", [](double* ops, int n) {
        if (n < 2) return;
        if (ops[1] == 0) {
            throw std::runtime_error("Division by zero");
        }
        ops[0] = ops[0] / ops[1];
    });

    // Add your other existing commands here...
}

bool CommandSystem::registerCommand(const std::string& unicode, CommandFunction func) {
    std::lock_guard<std::mutex> lock(commandMutex);
    
    auto& errorSystem = ErrorSystem::getInstance();
    if (!errorSystem.checkUnicodeValid(unicode)) {
        return false;
    }

    commandMap[unicode] = std::move(func);
    return true;
}

bool CommandSystem::processInput(const std::string& input, double& result) {
    std::lock_guard<std::mutex> lock(commandMutex);
    
    try {
        // Parse the input
        auto ast = parser->parse(input);
        if (!ast) {
            std::cerr << "Parse error: " << parser->getLastError() << std::endl;
            return false;
        }

        // Evaluate the expression
        result = ast->evaluate();
        lastResult = result;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Execution error: " << e.what() << std::endl;
        return false;
    }
}

bool CommandSystem::executeCommand(const std::string& unicode, double* operands, int numOperands) {
    auto it = commandMap.find(unicode);
    if (it == commandMap.end()) {
        auto& errorSystem = ErrorSystem::getInstance();
        errorSystem.reportError(ERR_UNRECOGNIZED_COMMAND, "Unknown command: " + unicode);
        return false;
    }

    try {
        it->second(operands, numOperands);
        return true;
    }
    catch (const std::exception& e) {
        auto& errorSystem = ErrorSystem::getInstance();
        errorSystem.reportError(ERR_RUNTIME, e.what());
        return false;
    }
}

// Example command implementation with error checking
void cmdDiv(double* operands, int numOperands) {
    auto& errorSystem = ErrorSystem::getInstance();
    
    WOFLANG_CHECK_OPERANDS(numOperands, 2);
    WOFLANG_CHECK_DIV_ZERO(operands[1]);
    
    operands[0] = operands[0] / operands[1];
    
    // Check result is in valid range
    WOFLANG_CHECK_RANGE(operands[0], -1e9, 1e9);  // Example range
}

void CommandSystem::setErrorCallback(std::function<void(int)> callback) {
    std::lock_guard<std::mutex> lock(commandMutex);
    errorCallback = std::move(callback);
}

void CommandSystem::handleError(int errorCode) {
    if (errorCallback) {
        errorCallback(errorCode);
    }
}

void CommandSystem::logCommand(const std::string& unicode, bool success) {
    // Implement your logging logic here
    std::cout << "Command " << unicode << (success ? " succeeded" : " failed") << std::endl;
}

} // namespace woflang