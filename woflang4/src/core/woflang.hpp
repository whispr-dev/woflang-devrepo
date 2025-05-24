// File: woflang.hpp
#pragma once

#include <vector>         // Required for std::vector
#include "wofltype.hpp" // **Corrected**: Now includes the definition of woflvalue from wofltype.hpp

/**
 * @brief Main class for the woflang language core.
 * This class likely manages the runtime stack and operations.
 */
class woflang
{
public:
    // --- Fixes for errors on lines 20 and 21 ---
    // The original errors suggested a missing return type and/or
    // incorrect syntax/specifiers (like 'override') for a 'pop' function.
    // Assuming 'pop' is a member function that retrieves a woflvalue from a stack.
    woflvalue pop(); // Corrected: Added 'woflvalue' as the return type.
                    // Removed any problematic 'override' or incorrect syntax.

    // --- Fixes for errors on line 41 ---
    // The errors here were due to 'woflvalue' being an undeclared identifier
    // when used with std::vector. Including "wofltype.hpp" resolves this.
    std::vector<woflvalue> valueStack;

    // Constructor and Destructor (using defaults for simplicity)
    woflang() = default;
    ~woflang() = default;

    // Example member function: push a woflvalue onto the stack
    void push(const woflvalue& val);
};

// --- Minimal implementations for completeness (typically in a .cpp file) ---
// For the purpose of providing a complete, compilable artifact,
// these simple implementations are included here. In a larger project,
// you would usually define these in a separate 'woflang.cpp' file.

/**
 * @brief Pops a woflvalue from the top of the internal stack.
 * @return The woflvalue popped from the stack.
 * @note This is a minimal implementation and might need error handling
 * (e.g., throwing an exception if the stack is empty).
 */
inline woflvalue woflang::pop() {
    if (!valueStack.empty()) {
        woflvalue val = valueStack.back(); // Get the last element
        valueStack.pop_back();            // Remove the last element
        return val;
    }
    // In a real application, you'd likely throw an exception or handle this error.
    // For compilation, returning a default-constructed woflvalue.
    return {}; // Default-constructed woflvalue
}

/**
 * @brief Pushes a woflvalue onto the top of the internal stack.
 * @param val The woflvalue to push.
 */
inline void woflang::push(const woflvalue& val) {
    valueStack.push_back(val);
}