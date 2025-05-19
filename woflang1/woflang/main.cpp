// `main.cpp` attempt at a C++ version of woflang

// main.cpp
#include "woflang_config.h"
#include "constants.h"
#include "commands.h"
#include "utils.h"
#include "error_system.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

int main(int argc, char* argv[]) {
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
        
    // Get command system instance
    auto& cmdSystem = woflang::CommandSystem::getInstance();
    auto& dict = woflang::CommandDictionary::getInstance();
    auto& errorSystem = woflang::ErrorSystem::getInstance();

    // Initialize command system
    if (!cmdSystem.initialize()) {
        std::cerr << "Failed to initialize command system" << std::endl;
        return 1;
    }

    // Load dictionary if provided
    if (argc > 1) {
        if (!dict.loadFromFile(argv[1])) {
            std::cerr << "Failed to load dictionary file: " << argv[1] << std::endl;
            return 1;
        }
    }

    // Main processing loop
    std::cout << "WoflangCPP v0.1" << std::endl;
    std::cout << "Enter expressions (or 'exit' to quit):" << std::endl;

    std::string input;
    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") {
            break;
        }

        if (input.empty()) {
            continue;
        }

        double result;
        if (cmdSystem.processInput(input, result)) {
            std::cout << "= " << result << std::endl;
        } else {
            if (errorSystem.getLastError() != 0) {
                std::cout << "Would you like to continue? (y/n): ";
                char response;
                std::cin >> response;
                std::cin.ignore(); // Clear the newline
                if (response != 'y' && response != 'Y') {
                    break;
                }
                errorSystem.clearError();
            }
        }
    }    

    // Load the command dictionary
    if (!dict.loadFromFile("woflang_commands.dict")) {
        std::cerr << "Failed to load command dictionary" << std::endl;
        return 1;
    }

    // Get command system instance
    auto& cmdSystem = woflang::CommandSystem::getInstance();
    
    // Set up error callback
    cmdSystem.setErrorCallback([](int errorCode) {
        handleError(errorCode); // Your existing error handling function
    });

    // Load dictionary if provided as argument
    if (argc > 1) {
        std::string dictionaryFile = argv[1];
        if (!cmdSystem.loadDictionary(dictionaryFile)) {
            std::cerr << "Failed to load dictionary file" << std::endl;
            return 1;
        }
    }

    // Register basic commands
    // Mathematical Operations
    cmdSystem.registerCommand("⊕", [](double* ops, int n) {
        if (n < 2) return;
        ops[0] = ops[0] + ops[1];
    });

    cmdSystem.registerCommand("⊖", [](double* ops, int n) {
        if (n < 2) return;
        ops[0] = ops[0] - ops[1];
    });

    cmdSystem.registerCommand("⊗", [](double* ops, int n) {
        if (n < 2) return;
        ops[0] = ops[0] * ops[1];
    });

    cmdSystem.registerCommand("⊘", [](double* ops, int n) {
        if (n < 2) return;
        if (ops[1] == 0) {
            handleError(ERR_RUNTIME_DIV_ZERO);
            return;
        }
        ops[0] = ops[0] / ops[1];
    });

    // Logical Operations
    cmdSystem.registerCommand("∧", [](double* ops, int n) {
        if (n < 2) return;
        ops[0] = (ops[0] != 0 && ops[1] != 0) ? 1.0 : 0.0;
    });

    cmdSystem.registerCommand("∨", [](double* ops, int n) {
        if (n < 2) return;
        ops[0] = (ops[0] != 0 || ops[1] != 0) ? 1.0 : 0.0;
    });

    // Start command processing loop
    std::string input;
    std::cout << "WoflangCPP interpreter (enter 'exit' to quit)" << std::endl;
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        // Basic command parsing - this should be replaced with your actual parser
        if (input.length() >= 1) {
            std::string command = input.substr(0, 1);
            double operands[] = {1.0, 1.0}; // Example operands - replace with actual parsing
            
            if (!cmdSystem.executeCommand(command, operands, 2)) {
                std::cerr << "Command execution failed" << std::endl;
                continue;
            }

            std::cout << "Result: " << operands[0] << std::endl;
        }
    }

        auto& cmdSystem = woflang::CommandSystem::getInstance();
        auto& dict = woflang::CommandDictionary::getInstance();
        woflang::Parser parser(cmdSystem, dict);
    
        std::string input;
        while (std::getline(std::cin, input)) {
            auto ast = parser.parse(input);
            if (ast) {
                try {
                    double result = ast->evaluate();
                    std::cout << "Result: " << result << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Evaluation error: " << e.what() << std::endl;
                }
            } else {
                std::cout << "Parse error: " << parser.getLastError() << std::endl;
            }
        }
    }

    auto& cmdSystem = woflang::CommandSystem::getInstance();
    auto& errorSystem = woflang::ErrorSystem::getInstance();
    
    // Register custom error handler
    errorSystem.registerErrorHandler(ERR_RUNTIME, [](const std::string& ctx) {
        std::cerr << "Runtime error occurred: " << ctx << std::endl;
        // Add any custom error handling logic
    });
    
    // Example command registration with error checking
    cmdSystem.registerCommand("÷", [](double* ops, int n) {
        cmdDiv(ops, n);
    });
    
    // Main processing loop
    while (true) {
        try {
            // Process commands...
            if (errorSystem.getLastError() != 0) {
                std::cout << "Last operation failed. Continue? (y/n): ";
                char response;
                std::cin >> response;
                if (response != 'y') break;
                errorSystem.clearError();
            }
        } catch (const std::exception& e) {
            errorSystem.reportError(ERR_RUNTIME, e.what());
        }
    }

    return 0;
}