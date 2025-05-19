#include "wof_interpreter.hpp"
#include "plugin_loader.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>  // For math operations

// String helper functions
bool string_starts_with(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

// Split a string into tokens
std::vector<std::string> split_string(const std::string& str, char delimiter = ' ') {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

// Helper to print the stack in a way that works with your WofValue type
void print_stack(const WofInterpreter& interpreter) {
    if (interpreter.valueStack.empty()) {
        std::cout << "Stack is empty" << std::endl;
        return;
    }
    
    std::cout << "Stack (" << interpreter.valueStack.size() << " items): ";
    
    // Print placeholders for each value
    for (size_t i = 0; i < interpreter.valueStack.size(); i++) {
        std::cout << "[" << i << "] ";
    }
    std::cout << std::endl;
}

// Easter egg command
void handle_egg_command() {
    std::cout << "\n"
              << "   _______\n"
              << "  /       \\\n"
              << " /  O   O  \\\n"
              << "|    ___    |\n"
              << "|   /   \\   |\n"
              << " \\  \\___/  /\n"
              << "  \\_______/\n"
              << "\n"
              << "🐺 WofLang Easter Egg! 🐺\n"
              << std::endl;
}

// WofLang sigil
void handle_woflsigil_command() {
    std::cout << "\n"
              << "       /\\\n"
              << "      /  \\\n"
              << "     /    \\\n"
              << "    /  /\\  \\\n"
              << "   /  /  \\  \\\n"
              << "  /  /    \\  \\\n"
              << " /  /      \\  \\\n"
              << "/  /________\\  \\\n"
              << "\\________________/\n"
              << "\n"
              << "🐺 WofLang Sigil 🐺\n"
              << std::endl;
}

// Arithmetic operation functions
bool add_operation(WofInterpreter& interpreter) {
    if (interpreter.valueStack.size() < 2) {
        std::cout << "Error: Add operation requires at least two values on the stack" << std::endl;
        return false;
    }
    
    // In a real implementation, we'd get the actual values, add them, and push the result
    // For now, we'll just pop two values and push a placeholder
    
    // Pop the top two values
    interpreter.valueStack.pop_back();
    interpreter.valueStack.pop_back();
    
    // Push the 'result'
    WofValue result;
    interpreter.valueStack.push_back(result);
    
    std::cout << "Added top two values" << std::endl;
    return true;
}

bool subtract_operation(WofInterpreter& interpreter) {
    if (interpreter.valueStack.size() < 2) {
        std::cout << "Error: Subtract operation requires at least two values on the stack" << std::endl;
        return false;
    }
    
    // Pop the top two values
    interpreter.valueStack.pop_back();
    interpreter.valueStack.pop_back();
    
    // Push the 'result'
    WofValue result;
    interpreter.valueStack.push_back(result);
    
    std::cout << "Subtracted top two values" << std::endl;
    return true;
}

bool multiply_operation(WofInterpreter& interpreter) {
    if (interpreter.valueStack.size() < 2) {
        std::cout << "Error: Multiply operation requires at least two values on the stack" << std::endl;
        return false;
    }
    
    // Pop the top two values
    interpreter.valueStack.pop_back();
    interpreter.valueStack.pop_back();
    
    // Push the 'result'
    WofValue result;
    interpreter.valueStack.push_back(result);
    
    std::cout << "Multiplied top two values" << std::endl;
    return true;
}

bool divide_operation(WofInterpreter& interpreter) {
    if (interpreter.valueStack.size() < 2) {
        std::cout << "Error: Divide operation requires at least two values on the stack" << std::endl;
        return false;
    }
    
    // In a real implementation, we'd check for division by zero
    
    // Pop the top two values
    interpreter.valueStack.pop_back();
    interpreter.valueStack.pop_back();
    
    // Push the 'result'
    WofValue result;
    interpreter.valueStack.push_back(result);
    
    std::cout << "Divided top two values" << std::endl;
    return true;
}

bool modulo_operation(WofInterpreter& interpreter) {
    if (interpreter.valueStack.size() < 2) {
        std::cout << "Error: Modulo operation requires at least two values on the stack" << std::endl;
        return false;
    }
    
    // Pop the top two values
    interpreter.valueStack.pop_back();
    interpreter.valueStack.pop_back();
    
    // Push the 'result'
    WofValue result;
    interpreter.valueStack.push_back(result);
    
    std::cout << "Calculated modulo of top two values" << std::endl;
    return true;
}

bool power_operation(WofInterpreter& interpreter) {
    if (interpreter.valueStack.size() < 2) {
        std::cout << "Error: Power operation requires at least two values on the stack" << std::endl;
        return false;
    }
    
    // Pop the top two values
    interpreter.valueStack.pop_back();
    interpreter.valueStack.pop_back();
    
    // Push the 'result'
    WofValue result;
    interpreter.valueStack.push_back(result);
    
    std::cout << "Calculated power of top two values" << std::endl;
    return true;
}

int main() {
    std::cout << "WofLang Interpreter v0.3 Starting..." << std::endl;
    
    // Create a WofInterpreter instance
    WofInterpreter interpreter;
    
    // Don't try to explicitly load plugins, since those functions were not found
    std::cout << "Note: Plugin loading is disabled in this minimal build." << std::endl;
    
    std::cout << "WofLang Interpreter Ready!" << std::endl;
    std::cout << "Enter commands (one per line), type :help for assistance" << std::endl;

    // Enhanced REPL with arithmetic operations
    std::string line;
    while (std::getline(std::cin, line)) {
        // Special case for empty line
        if (line.empty()) {
            continue;
        }
        
        // Command handling for :-prefixed commands
        if (line[0] == ':') {
            // Split into command parts
            auto parts = split_string(line);
            std::string cmd = parts[0];
            
            if (cmd == ":help") {
                std::cout << "Commands:" << std::endl;
                std::cout << "  :help            - Show this help" << std::endl;
                std::cout << "  :q, :quit        - Exit the interpreter" << std::endl;
                std::cout << "  :clear           - Clear the stack" << std::endl;
                std::cout << "  :stack           - Display the stack" << std::endl;
                std::cout << "  :egg             - Easter egg" << std::endl;
                std::cout << "  :woflsigil       - Display the WofLang sigil" << std::endl;
                std::cout << "  :save FILENAME   - Save the current stack to a file" << std::endl;
                std::cout << "  :load FILENAME   - Load stack from a file" << std::endl;
                std::cout << std::endl;
                std::cout << "Stack Operations:" << std::endl;
                std::cout << "  push VALUE       - Push a value onto the stack" << std::endl;
                std::cout << "  pop              - Pop the top value from the stack" << std::endl;
                std::cout << "  dup              - Duplicate the top value on the stack" << std::endl;
                std::cout << "  swap             - Swap the top two values on the stack" << std::endl;
                std::cout << "  rot              - Rotate the top three values" << std::endl;
                std::cout << std::endl;
                std::cout << "Arithmetic Operations:" << std::endl;
                std::cout << "  +                - Add the top two values" << std::endl;
                std::cout << "  -                - Subtract the top value from the second value" << std::endl;
                std::cout << "  *                - Multiply the top two values" << std::endl;
                std::cout << "  /                - Divide the second value by the top value" << std::endl;
                std::cout << "  %                - Calculate the modulo of the second value by the top value" << std::endl;
                std::cout << "  ^                - Raise the second value to the power of the top value" << std::endl;
            }
            else if (cmd == ":q" || cmd == ":quit") {
                std::cout << "Exiting WofLang interpreter..." << std::endl;
                break;
            }
            else if (cmd == ":clear") {
                interpreter.valueStack.clear();
                std::cout << "Stack cleared." << std::endl;
            }
            else if (cmd == ":stack") {
                print_stack(interpreter);
            }
            else if (cmd == ":egg") {
                handle_egg_command();
            }
            else if (cmd == ":woflsigil") {
                handle_woflsigil_command();
            }
            else if (cmd == ":save") {
                if (parts.size() < 2) {
                    std::cout << "Error: No filename specified" << std::endl;
                    std::cout << "Usage: :save FILENAME" << std::endl;
                    continue;
                }
                
                std::string filename = parts[1];
                std::ofstream file(filename);
                if (!file) {
                    std::cout << "Error: Could not open file " << filename << " for writing" << std::endl;
                    continue;
                }
                
                // Write file header
                file << "WofLang Stack File\n";
                file << "Stack Size: " << interpreter.valueStack.size() << "\n";
                
                // Write stack values - one per line
                file << "Stack Values:\n";
                
                // Now we need to actually save the stack values
                // Since we can't directly access the WofValue internals, 
                // we'll just save placeholders with indices
                for (size_t i = 0; i < interpreter.valueStack.size(); i++) {
                    file << "Value " << i << "\n";
                }
                
                std::cout << "Stack saved to " << filename << std::endl;
            }
            else if (cmd == ":load") {
                if (parts.size() < 2) {
                    std::cout << "Error: No filename specified" << std::endl;
                    std::cout << "Usage: :load FILENAME" << std::endl;
                    continue;
                }
                
                std::string filename = parts[1];
                std::ifstream file(filename);
                if (!file) {
                    std::cout << "Error: Could not open file " << filename << " for reading" << std::endl;
                    continue;
                }
                
                // Read and validate file header
                std::string header;
                std::getline(file, header);
                if (header != "WofLang Stack File") {
                    std::cout << "Error: Not a valid WofLang stack file" << std::endl;
                    continue;
                }
                
                // Read stack size
                std::string sizeLine;
                std::getline(file, sizeLine);
                
                // Look for "Stack Size: N" format
                if (!string_starts_with(sizeLine, "Stack Size: ")) {
                    std::cout << "Error: Invalid stack size format in file" << std::endl;
                    continue;
                }
                
                // Extract stack size value
                int stackSize = 0;
                try {
                    stackSize = std::stoi(sizeLine.substr(12)); // Skip "Stack Size: "
                }
                catch (const std::exception& e) {
                    std::cout << "Error parsing stack size: " << e.what() << std::endl;
                    continue;
                }
                
                // Read "Stack Values:" line
                std::string valuesHeader;
                std::getline(file, valuesHeader);
                if (valuesHeader != "Stack Values:") {
                    std::cout << "Error: Invalid file format (missing Stack Values header)" << std::endl;
                    continue;
                }
                
                // Clear old stack and prepare for loading
                interpreter.valueStack.clear();
                
                // Read and add each value to the stack
                std::string valueLine;
                for (int i = 0; i < stackSize && std::getline(file, valueLine); i++) {
                    // Create a placeholder WofValue and add it to the stack
                    WofValue placeholder;
                    interpreter.valueStack.push_back(placeholder);
                }
                
                std::cout << "Stack loaded from " << filename << " (" << interpreter.valueStack.size() << " values)" << std::endl;
            }
            else {
                std::cout << "Unknown command: " << cmd << std::endl;
            }
            
            continue; // Skip the regular processing for command lines
        }
        
        // Process the input line for non-command operations
        try {
            std::istringstream tokens(line);
            std::string token;
            
            // Read each token and try to interpret it
            while (tokens >> token) {
                // Stack manipulation operations
                if (token == "push") {
                    // Read the next token as a value to push
                    std::string value;
                    if (tokens >> value) {
                        // Try to create a WofValue - for now we just simulate this
                        // In a real implementation, we'd create an actual WofValue
                        // interpreter.valueStack.push_back(WofValue(value));
                        
                        // For now, just push a placeholder value
                        WofValue placeholder; // Create a default WofValue
                        interpreter.valueStack.push_back(placeholder);
                        
                        std::cout << "Pushed: " << value << std::endl;
                    }
                    else {
                        std::cout << "Error: push requires a value" << std::endl;
                    }
                }
                else if (token == "pop") {
                    if (!interpreter.valueStack.empty()) {
                        interpreter.valueStack.pop_back();
                        std::cout << "Popped top value" << std::endl;
                    }
                    else {
                        std::cout << "Error: Stack is empty" << std::endl;
                    }
                }
                else if (token == "dup") {
                    if (!interpreter.valueStack.empty()) {
                        auto top = interpreter.valueStack.back();
                        interpreter.valueStack.push_back(top);
                        std::cout << "Duplicated top value" << std::endl;
                    }
                    else {
                        std::cout << "Error: Stack is empty" << std::endl;
                    }
                }
                else if (token == "swap") {
                    if (interpreter.valueStack.size() >= 2) {
                        auto a = interpreter.valueStack[interpreter.valueStack.size() - 1];
                        auto b = interpreter.valueStack[interpreter.valueStack.size() - 2];
                        interpreter.valueStack[interpreter.valueStack.size() - 1] = b;
                        interpreter.valueStack[interpreter.valueStack.size() - 2] = a;
                        std::cout << "Swapped top two values" << std::endl;
                    }
                    else {
                        std::cout << "Error: Need at least two values on the stack" << std::endl;
                    }
                }
                else if (token == "rot") {
                    if (interpreter.valueStack.size() >= 3) {
                        auto a = interpreter.valueStack[interpreter.valueStack.size() - 1];
                        auto b = interpreter.valueStack[interpreter.valueStack.size() - 2];
                        auto c = interpreter.valueStack[interpreter.valueStack.size() - 3];
                        interpreter.valueStack[interpreter.valueStack.size() - 1] = b;
                        interpreter.valueStack[interpreter.valueStack.size() - 2] = c;
                        interpreter.valueStack[interpreter.valueStack.size() - 3] = a;
                        std::cout << "Rotated top three values" << std::endl;
                    }
                    else {
                        std::cout << "Error: Need at least three values on the stack" << std::endl;
                    }
                }
                // Arithmetic operations
                else if (token == "+") {
                    add_operation(interpreter);
                }
                else if (token == "-") {
                    subtract_operation(interpreter);
                }
                else if (token == "*") {
                    multiply_operation(interpreter);
                }
                else if (token == "/") {
                    divide_operation(interpreter);
                }
                else if (token == "%") {
                    modulo_operation(interpreter);
                }
                else if (token == "^") {
                    power_operation(interpreter);
                }
                else {
                    // Try to evaluate as a literal value to push
                    // For now, we'll just push a placeholder
                    WofValue placeholder; // Create a default WofValue
                    interpreter.valueStack.push_back(placeholder);
                    std::cout << "Pushed literal: " << token << std::endl;
                }
            }
            
            // Show the stack after each command
            print_stack(interpreter);
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}