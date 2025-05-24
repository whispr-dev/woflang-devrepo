// File: tokenizer.cpp

// --- Fix for C1083 error: Cannot open include file ---
// This includes the woflvalue type.
// Assuming wofltype.hpp is located at C:\woflang4\src\core\wofltype.hpp
// and this tokenizer.cpp file is at C:\woflang4\src\io\tokenizer.cpp.
// The relative path "../core/wofltype.hpp" is correct for this structure.
// Please ensure the file C:\woflang4\src\core\wofltype.hpp actually exists.
#include "../core/wofltype.hpp" // **Corrected**: Now includes wofltype.hpp
#include "../core/woflang.hpp" // Also include woflang.hpp if you need its types/classes here

#include <iostream> // For console output in a simple example
#include <string>   // For std::string example usage

/**
 * @brief A simple example main function for the tokenizer component.
 * This demonstrates that woflvalue and woflang types are now recognized.
 */
int main() {
    std::cout << "--- Tokenizer Component Test ---" << std::endl;

    // Demonstrate woflvalue usage
    woflvalue my_value(42); // Corrected: woflvalue type
    std::cout << "Created woflvalue with int_value: " << my_value.int_value << std::endl;

    // Demonstrate woflang class usage
    woflang lang_processor;
    lang_processor.push(woflvalue(100)); // Corrected: woflvalue type
    lang_processor.push(woflvalue(200)); // Corrected: woflvalue type

    std::cout << "Pushed two values onto woflang stack." << std::endl;

    if (!lang_processor.valueStack.empty()) {
        woflvalue popped_val = lang_processor.pop(); // Corrected: woflvalue type
        std::cout << "Popped value from woflang stack: " << popped_val.int_value << std::endl;
    } else {
        std::cout << "woflang stack is empty." << std::endl;
    }

    std::cout << "Tokenizer component test finished." << std::endl;

    return 0;
}