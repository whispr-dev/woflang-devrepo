// string_processing.cpp
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <immintrin.h>  // Include SIMD intrinsics

// Converts a string to a double-precision float
double stringToDouble(const std::string& str) {
    double result = 0.0;
    double place = 1.0;
    bool isFraction = false;

    for (char c : str) {
        if (c == '.') {
            isFraction = true;
            continue;
        }
        if (c < '0' || c > '9') {
            std::cerr << "Error: Invalid character in string to double conversion" << std::endl;
            return 0.0; // or some error handling
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
    return str1 + str2;
}

// Optimized string handler function (simulating SIMD using a basic example)
void stringHandler(std::string& str) {
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
