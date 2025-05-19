// `logic.h` an attempt to make a C++ version of woflang

#pragma once
#include <vector>

// Constants used in logic operations
extern const double E;
extern const double FUZZY_100;
extern const double ZERO;
extern const double ONE;
extern const double FUZZY_50;

// Buffers for SIMD-like vector operations
extern std::vector<double> vector1;
extern std::vector<double> vector2;
extern std::vector<double> result_vector;

// Function declarations

// Convert binary to fuzzy logic (0 or 1 to 0 or 100)
void binaryToFuzzy(double& value);

// Convert fuzzy logic to binary (0-100 to 0 or 1)
void fuzzyToBinary(double& value);

// Compare two vectors and store the result in result_vector
void cmpRoutine(const std::vector<double>& vec1, const std::vector<double>& vec2, std::vector<double>& result);

// Vector AND operation (element-wise minimum)
void vectorAndOptimized(const std::vector<double>& vec1, const std::vector<double>& vec2, std::vector<double>& result);

// Fuzzy OR operation (element-wise maximum)
void orRoutine(double& a, double b);

// Fuzzy XOR operation (element-wise difference)
void xorRoutine(double& a, double b);

// Fuzzy NOT operation (inversion)
void notRoutine(double& a);

// Fuzzy NAND operation (NOT of AND)
void nandRoutine(double& a, double b);

// Fuzzy NOR operation (NOT of OR)
void norRoutine(double& a, double b);

// IF routine for fuzzy logic
void ifRoutine(double& result, double condition, double trueResult, double falseResult);

// Implication routine for fuzzy logic
void implicationRoutine(double& a, double b);

// Not-implication routine for fuzzy logic
void nimplyRoutine(double& a, double b);

// NULL routine (reset to zero)
void nullRoutine(double& a);

// Inhibition routine (fuzzy inhibition)
void inhibitionRoutine(double& a, double b);

// Buffer routine (no operation needed in C++ context)
void bufferRoutine(double& a);

// Inhibition XY routine (fuzzy inhibition with two variables)
void inhibitionXYRoutine(double& a, double b);

// Equivalence routine (fuzzy equivalence)
void equivalenceRoutine(double& a, double b);

// Identity routine (always returns 100 in fuzzy logic)
void identityRoutine(double& a);

// Command logic handler for different operations
void logicHandler(char command, double& a, double b);
