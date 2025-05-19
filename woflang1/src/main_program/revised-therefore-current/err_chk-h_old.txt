// `err_chk.h` an attempt to make a C++ woflang

#pragma once
#include <string>

void reportError(int errorCode, const std::string& context);
void checkHeader(const std::string& header);
void checkBlockOrder(int currentBlock, int expectedBlock);
void handleError(int errorCode);
void checkMemoryAddress(void* ptr);
void checkStringOperation(const std::string& operation, const std::string& str);
void checkMathOperation(double a, double b, const std::string& operation);
void checkLogicOperation(bool condition, const std::string& operation);

// Ensure each error code has a unique value
enum ErrorCode {
    ERR_HEADER_MISSING = 0x01,
    ERR_BLOCK_ORDER = 0x02,
    ERR_UNRECOGNIZED = 0x03,
    ERR_TYPE_MISMATCH = 0x04,
    ERR_RUNTIME = 0x05,
    ERR_OUT_OF_BOUNDS = 0xFF05,
    ERR_SOCKET_CREATION = 0x06,
    ERR_BIND = 0x07,
    ERR_LISTEN = 0x08,
    ERR_ACCEPT = 0x09,
    ERR_CLOSE = 0x0A,
    ERR_ATTRIBUTE = 0x0B,
    ERR_RUNTIME_DIV_ZERO = 0x11,  // Keep unique values
    ERR_RUNTIME_NULL_PTR = 0x12,
    ERR_RUNTIME_OVF = 0x13,
    ERR_MEM_INVALID_ADDRESS = 0x40,
    ERR_MEM_INVALID_OP = 0x41,
    ERR_STRING_NULL_PTR = 0x30,
    ERR_STRING_OVERFLOW = 0x31,
    ERR_STRING_INVALID_OP = 0x32,
    ERR_LOGIC_UNDEFINED_OP = 0x20,
    ERR_LOGIC_INVALID_COND = 0x21,
    ERR_LOGIC_INCONSISTENT = 0x22,
    ERR_MATH_OVERFLOW = 0x14,
    ERR_MATH_DIV_ZERO = 0x15, // Ensure different values
    ERR_MATH_INVALID_OPERAND = 0x16, // Ensure different values
    ERR_FP_EXCEPTION = 0x0C,
    ERR_FP_OVERFLOW = 0x0D,
    ERR_FP_UNDERFLOW = 0x0E,
    ERR_FP_INVALID = 0x0F
    };


// Add more function declarations as needed for other error checks

int main() {
    // Your code...
    return 0;
}
