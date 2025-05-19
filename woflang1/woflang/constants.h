// constants.h
#pragma once
#include "woflang_config.h"
#include <cmath>
#include <string>

namespace woflang {
namespace constants {

// Mathematical constants
constexpr double PI = 3.14159265358979323846;
constexpr double E = 2.71828182845904523536;
constexpr double GOLDEN_RATIO = 1.61803398874989484820;
constexpr double SQRT_2 = 1.41421356237309504880;

// Fuzzy logic constants
constexpr double FUZZY_TRUE = 100.0;
constexpr double FUZZY_FALSE = 0.0;
constexpr double FUZZY_THRESHOLD = 50.0;
constexpr double FUZZY_EPSILON = 1e-10;

// System limits
constexpr size_t MIN_OPERANDS = 1;
constexpr size_t MAX_STACK_DEPTH = 100;
constexpr double MAX_NUMERIC_VALUE = 1e9;
constexpr double MIN_NUMERIC_VALUE = -1e9;

// Error thresholds
constexpr double DIVISION_EPSILON = 1e-10;
constexpr int MAX_ITERATION_COUNT = 1000;
constexpr double CONVERGENCE_THRESHOLD = 1e-6;

// File and path constants
const std::string DEFAULT_DICTIONARY_FILE = "woflang_commands.dict";
const std::string DEFAULT_CONFIG_FILE = "woflang.conf";
const std::string LOG_FILE = "woflang.log";

// Command categories
enum class CommandCategory {
    ARITHMETIC,
    LOGICAL,
    TRIGONOMETRIC,
    MATRIX,
    VECTOR,
    SYSTEM,
    CUSTOM
};

// Operator precedence
enum class OperatorPrecedence {
    LOWEST = 0,
    ASSIGNMENT = 1,
    LOGICAL_OR = 2,
    LOGICAL_AND = 3,
    EQUALITY = 4,
    RELATIONAL = 5,
    ADDITIVE = 6,
    MULTIPLICATIVE = 7,
    UNARY = 8,
    HIGHEST = 9
};

// Unicode ranges for valid operators
struct UnicodeRange {
    uint32_t start;
    uint32_t end;
};

constexpr UnicodeRange MATH_OPERATORS = {0x2200, 0x22FF};
constexpr UnicodeRange SUPPLEMENTAL_OPERATORS = {0x2A00, 0x2AFF};
constexpr UnicodeRange CJK_SYMBOLS = {0x4E00, 0x9FFF};
constexpr UnicodeRange KANGXI_RADICALS = {0x2F00, 0x2FDF};

// Error message templates
namespace messages {
    const std::string DIVISION_BY_ZERO = "Division by zero error";
    const std::string INVALID_OPERAND = "Invalid operand provided";
    const std::string STACK_OVERFLOW = "Stack overflow error";
    const std::string UNKNOWN_COMMAND = "Unknown command";
    const std::string INVALID_SYNTAX = "Invalid syntax";
    const std::string FILE_NOT_FOUND = "File not found";
}

// Default configuration values
namespace defaults {
    constexpr bool DEBUG_MODE = false;
    constexpr int THREAD_POOL_SIZE = 4;
    constexpr size_t BUFFER_SIZE = 4096;
    constexpr double DEFAULT_TIMEOUT = 5.0;  // seconds
}

} // namespace constants
} // namespace woflang