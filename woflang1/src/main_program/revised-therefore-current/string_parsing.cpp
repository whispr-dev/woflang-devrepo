// `string_parsing.cpp` a C++ attempt at creating woflang

#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <immintrin.h>  // Include SIMD intrinsics

// Error code constants (from earlier list)
const int ERR_STRING_INVALID_OP = 0x32;
const int ERR_RUNTIME_DIV_ZERO = 0x11;
const int ERR_RUNTIME_NULL_PTR = 0x12;
const int ERR_STRING_OVERFLOW = 0x31;

// Utility function to print errors based on error code
void handleError(int errorCode) {
    switch (errorCode) {
        case ERR_STRING_INVALID_OP:
            printError("Invalid string operation");
            break;
        case ERR_RUNTIME_DIV_ZERO:
            printError("Division by zero");
            break;
        case ERR_RUNTIME_NULL_PTR:
            printError("Null pointer dereference");
            break;
        case ERR_STRING_OVERFLOW:
            printError("String overflow detected");
            break;
        default:
            printError("Unknown error occurred");
            break;
    }
}

// Converts a string to a double-precision float
double stringToDouble(const std::string& str) {
    if (str.empty()) {
        handleError(ERR_RUNTIME_NULL_PTR);
        return 0.0;
    }

    double result = 0.0;
    double place = 1.0;
    bool isFraction = false;
    int strLength = str.length();
    
    if (strLength > 50) { // Arbitrary limit to prevent overflow
        handleError(ERR_STRING_OVERFLOW);
        return 0.0;
    }

    for (char c : str) {
        if (c == '.') {
            if (isFraction) {
                handleError(ERR_STRING_INVALID_OP);  // More than one decimal point
                return 0.0;
            }
            isFraction = true;
            continue;
        }
        if (c < '0' || c > '9') {
            handleError(ERR_STRING_INVALID_OP);
            return 0.0; // Error handling for invalid characters
        }

        if (isFraction) {
            place /= 10.0;
            result += (c - '0') * place;
        } else {
            result = result * 10 + (c - '0');
        }
    }
    return result;
}

// Optimized addition routine
int addRoutine(int a, int b) {
    return a + b;
}

// Optimized concatenation routine using standard C++ string operations
std::string concatRoutine(const std::string& str1, const std::string& str2) {
    int totalLength = str1.length() + str2.length();
    if (totalLength > 100) { // Arbitrary limit for overflow protection
        handleError(ERR_STRING_OVERFLOW);
        return "";
    }

    return str1 + str2;
}

// Optimized string handler function (simulating SIMD using a basic example)
void stringHandler(std::string& str) {
    if (str.empty()) {
        handleError(ERR_RUNTIME_NULL_PTR);
        return;
    }

    // Example: Convert all characters to uppercase using standard C++
    for (char& c : str) {
        c = toupper(c);
    }
}

// Example usage
int main() {
    std::string str = "1234.5678";
    double floatResult = stringToDouble(str);
    std::cout << "Converted string to double: " << floatResult << std::endl;

    int sum = addRoutine(5, 10);
    std::cout << "Sum: " << sum << std::endl;

    std::string concatResult = concatRoutine("Hello, ", "world!");
    std::cout << "Concatenated string: " << concatResult << std::endl;

    std::string toUpper = "this is a test";
    stringHandler(toUpper);
    std::cout << "Uppercase string: " << toUpper << std::endl;

    return 0;
}
