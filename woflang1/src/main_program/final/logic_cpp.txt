// `logic.cpp` C++ attempt at woflang interpreter/parser

#include "logic.h"
#include "utils.h"  // Include utility functions for error handling
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include "logic.h"
#include "err_chk.h" // Make sure you include this to access error codes
#include <algorithm>
#include <cmath>
#include <vector>


// Define constants used in logic operations
const double E = 2.718281828459045;
const double FUZZY_100 = 100.0;
const double ZERO = 0.0;
const double ONE = 1.0;
const double FUZZY_50 = 50.0;

// Buffers to simulate SIMD-like vector operations
std::vector<double> vector1 = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
std::vector<double> vector2 = {7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0};
std::vector<double> result_vector(8, 0.0);

// Utility function to print errors based on error code
void handleError(int errorCode) {
    switch (errorCode) {
        case ERR_STRING_INVALID_OP:
            printError("Invalid string operation");
            break;
        case ERR_RUNTIME_DIV_ZERO:
            printError("Division by zero at runtime");
            break;
        case ERR_RUNTIME_NULL_PTR:
            printError("Null pointer at runtime");
            break;
        case ERR_STRING_OVERFLOW:
            printError("String overflow error");
            break;
        case ERR_OUT_OF_BOUNDS:
            printError("Out of bounds error");
            break;
        default:
            printError("Unknown error");
            break;
    }
}


// Convert binary to fuzzy logic (0 or 1 to 0 or 100)
void binaryToFuzzy(double& value) {
    value = (value != 0) ? FUZZY_100 : ZERO;
}

// Convert fuzzy logic to binary (0-100 to 0 or 1)
void fuzzyToBinary(double& value) {
    value = (value >= FUZZY_50) ? ONE : ZERO;
}

// Compare two vectors and store the result in result_vector
void cmpRoutine(const std::vector<double>& vec1, const std::vector<double>& vec2, std::vector<double>& result) {
    if (vec1.size() != vec2.size() || vec1.size() != result.size()) {
        handleError(ERR_OUT_OF_BOUNDS);
        return;
    }

    for (size_t i = 0; i < vec1.size(); ++i) {
        double diff = vec1[i] - vec2[i];
        result[i] = (diff > 0) ? diff : 0.0;
    }
}

// Vector AND operation (element-wise minimum)
void vectorAndOptimized(const std::vector<double>& vec1, const std::vector<double>& vec2, std::vector<double>& result) {
    if (vec1.size() != vec2.size() || vec1.size() != result.size()) {
        handleError(ERR_OUT_OF_BOUNDS);
        return;
    }

    for (size_t i = 0; i < vec1.size(); ++i) {
        result[i] = std::min(vec1[i], vec2[i]);
    }
}

// Fuzzy OR operation (element-wise maximum)
void orRoutine(double& a, double b) {
    a = std::max(a, b);
}

// Fuzzy XOR operation (element-wise difference)
void xorRoutine(double& a, double b) {
    a = std::abs(a - b);
}

// Fuzzy NOT operation (inversion)
void notRoutine(double& a) {
    a = FUZZY_100 - a;
}

// Fuzzy NAND operation (NOT of AND)
void nandRoutine(double& a, double b) {
    a = FUZZY_100 - std::min(a, b);
}

// Fuzzy NOR operation (NOT of OR)
void norRoutine(double& a, double b) {
    a = FUZZY_100 - std::max(a, b);
}

// IF routine for fuzzy logic
void ifRoutine(double& result, double condition, double trueResult, double falseResult) {
    result = (condition > 0) ? trueResult : falseResult;
}

// Implication routine for fuzzy logic
void implicationRoutine(double& a, double b) {
    a = std::min(FUZZY_100, FUZZY_100 - a + b);
}

// Not-implication routine for fuzzy logic
void nimplyRoutine(double& a, double b) {
    a = std::max(0.0, b - a);
}

// NULL routine (reset to zero)
void nullRoutine(double& a) {
    a = 0.0;
}

// Inhibition routine (fuzzy inhibition)
void inhibitionRoutine(double& a, double b) {
    a = std::min(a, FUZZY_100 - b);
}

// Buffer routine (no operation needed in C++ context)
void bufferRoutine(double& a) {
    // No operation
}

// Inhibition XY routine (fuzzy inhibition with two variables)
void inhibitionXYRoutine(double& a, double b) {
    a = std::min(FUZZY_100 - a, b);
}

// Equivalence routine (fuzzy equivalence)
void equivalenceRoutine(double& a, double b) {
    double minAB = std::min(a, b);
    double minNotA = FUZZY_100 - a;
    double minNotB = FUZZY_100 - b;
    a = minAB + std::min(minNotA, minNotB);
}

// Identity routine (always returns 100 in fuzzy logic)
void identityRoutine(double& a) {
    a = FUZZY_100;
}

// Command logic handler for different operations
// void logicHandler(char command, double& a, double b) {
//     switch (command) {
//        case '≈':
//            cmpRoutine(vector1, vector2, result_vector);
//            break;
//        case '&':
//            vectorAndOptimized(vector1, vector2, result_vector);
//           break;
//       case '∨':
//           orRoutine(a, b);
//            break;
//        case '⊕':
//            xorRoutine(a, b);
//            break;
//       case '¬':
//            notRoutine(a);
//            break;
//        case '⊼':
//            nandRoutine(a, b);
//            break;
//        case '⊽':
//            norRoutine(a, b);
//            break;
//        case '⇒':
//            ifRoutine(a, a, b, 0); // Example values for trueResult and falseResult
//            break;
//        case '⇔':
//            implicationRoutine(a, b);
//            break;
//        case '?':
//            nimplyRoutine(a, b);
//            break;
//        case '∄':
//            nullRoutine(a);/
//            break;
//        case '⊥':
//            inhibitionXYRoutine(a, b);
//            break;
//        case '∤':
//            bufferRoutine(a);
//            break;
//        case '↔':
//            inhibitionRoutine(a, b);
//            break;
//        case '≡':
//            equivalenceRoutine(a, b);
//            break;
//        case '≃':
//            identityRoutine(a);
//            break;
//        default:
//            handleError(ERR_STRING_INVALID_OP);
//            break;
//    }
// }
