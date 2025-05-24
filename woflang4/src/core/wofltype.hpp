// File: wofltype.hpp
#pragma once

/**
 * @brief Defines the woflvalue type.
 * This file is included by other parts of the woflang project
 * to ensure the woflvalue type is properly recognized by the compiler.
 *
 * NOTE: Fill in the actual members and methods for your woflvalue.
 * This is a minimal definition to satisfy compilation errors.
 */
struct woflvalue { // Corrected: woflvalue struct name
    // Example member (replace with your actual data)
    int int_value = 0;

    // You might add constructors, operators, etc., here
    // Example:
    woflvalue() = default;
    explicit woflvalue(int val) : int_value(val) {}
};