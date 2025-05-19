#include "wof_interpreter.hpp"
#include <iostream>
#include <string>

// Simple exploration utility to help understand WofValue
int main() {
    std::cout << "WofValue Explorer v0.1" << std::endl;
    
    // Try to create a WofValue
    std::cout << "Creating a WofValue..." << std::endl;
    WofValue value;
    
    // Print size of WofValue
    std::cout << "Size of WofValue: " << sizeof(WofValue) << " bytes" << std::endl;
    
    // Try to examine the types of values that can be created
    std::cout << "Testing different value creation methods:" << std::endl;
    
    // Try numeric values if possible
    try {
        // Try creating an integer WofValue
        // This is just a guess at the constructor signature
        // WofValue intValue(42);
        // std::cout << "  Created integer value: " << intValue.toString() << std::endl;
        std::cout << "  [SKIPPED] Integer constructor test" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "  Error creating integer value: " << e.what() << std::endl;
    }
    
    try {
        // Try creating a floating point WofValue
        // This is just a guess at the constructor signature
        // WofValue floatValue(3.14159);
        // std::cout << "  Created float value: " << floatValue.toString() << std::endl;
        std::cout << "  [SKIPPED] Float constructor test" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "  Error creating float value: " << e.what() << std::endl;
    }
    
    try {
        // Try creating a string WofValue
        // This is just a guess at the constructor signature
        // WofValue stringValue("Hello, WofLang!");
        // std::cout << "  Created string value: " << stringValue.toString() << std::endl;
        std::cout << "  [SKIPPED] String constructor test" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "  Error creating string value: " << e.what() << std::endl;
    }
    
    // Try stack operations on WofValues
    std::cout << "Testing stack operations:" << std::endl;
    
    WofInterpreter interpreter;
    std::cout << "  Initial stack size: " << interpreter.valueStack.size() << std::endl;
    
    // Push a value
    interpreter.valueStack.push_back(WofValue());
    std::cout << "  After push: " << interpreter.valueStack.size() << std::endl;
    
    // Pop a value
    if (!interpreter.valueStack.empty()) {
        interpreter.valueStack.pop_back();
        std::cout << "  After pop: " << interpreter.valueStack.size() << std::endl;
    }
    
    return 0;
}