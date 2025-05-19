// `command_beta.cpp` woflang interpreter/parser alter

#include "commands.h"
#include <iostream>
#include <unordered_map>
#include <functional>
#include <cmath>       // For mathematical operations
#include <bitset>      // For bitwise operations
#include <cstring>     // For memcpy
#include <curl/curl.h>
#include <cstdlib>     // For setenv
#include <iostream>
#include <algorithm> // For std::min and std::max

// Enum for command types
enum CommandType {
    CMD_CMP,
    CMD_ADD,
    CMD_SUB,
    CMD_MUL,
    CMD_DIV,
    CMD_EQ,
    CMD_DNE,
    CMD_GT,
    CMD_LT,
    CMD_GTE,
    CMD_LTE,
    CMD_AND,
    CMD_OR,
    CMD_XOR,
    CMD_NOT,
    CMD_NAND,
    CMD_NOR,
    CMD_IF,
    CMD_THEN,
    CMD_ELSE,
    CMD_WHILE,
    CMD_FOR,
    CMD_BUF,
    CMD_INHIBIT,
    CMD_EQUIV,
    CMD_IDENTITY,
    CMD_BIN2FUZZ,
    CMD_FUZZ2BIN,
    CMD_BOOL,
    CMD_COUNT,
    CMD_STR,
    CMD_VECTADD,
    CMD_VECTSUB,
    CMD_DOTPROD,
    CMD_MTRXDET,
    CMD_MTRXINV,
    CMD_3X3DET,
    CMD_MTRXAND,
    CMD_BREAK,
    CMD_END,
    CMD_DONE,
    CMD_EXIT,
    CMD_PROMPT,
    CMD_INPUT,
    CMD_SYSCALL,
    CMD_ECHO,
    CMD_HTTP,
    CMD_PROXY,
    CMD_USERAGENT,
    CMD_FUNC,
    CMD_ATTRIBUTE,
    CMD_TYPE,
    CMD_SERVER,
    CMD_WAIT,
    CMD_SLEEP,
    CMD_PRINT,
    CMD_CHAR,
    CMD_READ,
    CMD_MOVE,
    CMD_NULL,
    CMD_PATH,
    // Add more command types as needed
};

// Typedef for function pointer for command execution
typedef std::function<void(double*, int)> CommandFunction;

// Function prototypes
void cmdCmp (double*, int):
void cmdAdd(double*, int);
void cmdSub(double*, int);
void cmdMul(double*, int);
void cmdDiv(double*, int);
void cmdEq(double*, int);
void cmdDNE(double*, int);
void cmdGT(double*, int);
void cmdLT(double*, int);
void cmdGTE(double*, int);
void cmdLTE(double*, int);
void cmdAnd(double*, int);
void cmdOr(double*, int);
void cmdXor(double*, int);
void cmdNot(double*, int);
void cmdNand(double*, int);
void cmdNor(double*, int);
void cmdIf(double*, int);
void cmdThen(double*, int);
void cmdElse(double*, int);
void cmdWhile(double*, int);
void cmdFor(double*, int);
void cmdBuf(double*, int);
void cmdInhibit(double*, int);
void cmdEquiv(double*, int);
void cmdId(double*, int);
void cmdBin2Fuz(double*, int);
void cmdFuz2Bin(double*, int);
void cmdBool(double*, int);
void cmdCount(double*, int);
void cmdStr(double*, int);
void cmdVectAdd(double*, int);
void cmdVectSub(double*, int);
void cmdDotProd(double*, int);
void cmdMtrxDet(double*, int);
void cmdMtrxInv(double*, int);
void cmd3x3Det(double*, int);
void cmdMtrxAnd(double*, int);
void cmdBreak(double*, int);
void cmdEnd(double*, int);
void cmdDone(double*, int);
void cmdExit(double*, int);
void cmdPrompt(double*, int);
void cmdInput(double*, int);
void cmdSysCall(double*, int);
void cmdEcho(double*, int);
void cmdHttpGet(double*, int);
void cmdProxy(double*, int);
void cmdUserAgent(double*, int);
void cmdFunc(double*, int);
void cmdAttribute(double*, int);
void cmdType(double*, int);
void cmdServer(double*, int);
void cmdWait(double*, int);
void cmdSleep(double*, int);
void cmdPrint(double*, int);
void cmdChar(double*, int);
void cmdRead(double*, int);
void cmdMove(double*, int);
void cmdNull(double*, int);
void cmdPath(double*, int);

// Map command types to their functions
std::unordered_map<CommandType, CommandFunction> commandMap = {
    (CMD_CMP, cmdCmp),
    {CMD_ADD, cmdAdd},
    {CMD_SUB, cmdSub},
    {CMD_MUL, cmdMul},
    {CMD_DIV, cmdDiv},
    {CMD_EQ, cmdEq},
    {CMD_DNE, cmdDNE},
    {CMD_GT, cmdGT},
    {CMD_LT, cmdLT},
    {CMD_GTE, cmdGTE},
    {CMD_LTE, cmdLTE},
    {CMD_AND, cmdAnd},
    {CMD_OR, cmdOr},
    {CMD_XOR, cmdXor},
    {CMD_NOT, cmdNot},
    {CMD_NAND, cmdNand},
    {CMD_NOR, cmdNor},
    {CMD_IF, cmdIf},
    {CMD_THEN, cmdThen},
    {CMD_ELSE, cmdElse},
    {CMD_WHILE, cmdWhile},
    {CMD_FOR, cmdFor},
    {CMD_BUF, cmdBuf},
    {CMD_INHIBIT, cmdInhibit},
    {CMD_EQUIV, cmdEquiv},
    {CMD_IDENTITY, cmdId},
    {CMD_BIN2FUZZ, cmdBin2Fuz},
    {CMD_FUZZ2BIN, cmdFuz2Bin},
    {CMD_BOOL, cmdBool},
    {CMD_COUNT, cmdCount},
    {CMD_STR, cmdStr},
    {CMD_VECTADD, cmdVectAdd},
    {CMD_VECTSUB, cmdVectSub},
    {CMD_DOTPROD, cmdDotProd},
    {CMD_MTRXDET, cmdMtrxDet},
    {CMD_MTRXINV, cmdMtrxInv},
    {CMD_3X3DET, cmd3x3Det},
    {CMD_MTRXAND, cmdMtrxAnd},
    {CMD_BREAK, cmdBreak},
    {CMD_END, cmdEnd},
    {CMD_DONE, cmdDone},
    {CMD_EXIT, cmdExit},
    {CMD_PROMPT, cmdPrompt},
    {CMD_INPUT, cmdInput},
    {CMD_SYSCALL, cmdSysCall},
    {CMD_ECHO, cmdEcho},
    {CMD_HTTP, cmdHttpGet},  // Example, implement cmdHttpGet function
    {CMD_PROXY, cmdProxy},
    {CMD_USERAGENT, cmdUserAgent},
    {CMD_FUNC, cmdFunc},
    {CMD_ATTRIBUTE, cmdAttribute},
    {CMD_TYPE, cmdType},
    {CMD_SERVER, cmdServer},
    {CMD_WAIT, cmdWait},
    {CMD_SLEEP, cmdSleep},
    {CMD_PRINT, cmdPrint},
    {CMD_CHAR, cmdChar},
    {CMD_READ, cmdRead},
    {CMD_MOVE, cmdMove},
    {CMD_NULL, cmdNull},
    {CMD_PATH, cmdPath},
    // Add more command mappings here
};

// Implementing various command functions

// Implementing various command functions for fuzzy logic

// Utility function to clamp values to the range [0, 100]
double clamp(double value) {
    return std::max(0.0, std::min(100.0, value));
}

void cmdCmp(double& result, double a, double b) {
    result = (a > b) ? 100 : 0;  // Fuzzy comparison: returns 100 if 'a' > 'b', otherwise 0
}

void cmdAdd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double result = operands[0] + operands[1];
        result = std::min(result, 100.0);  // Clamp to max 100
        std::cout << "Result (ADD): " << result << std::endl;
    }
}

void cmdSub(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double result = operands[0] - operands[1];
        result = std::max(result, 0.0);  // Clamp to min 0
        std::cout << "Result (SUBTRACT): " << result << std::endl;
    }
}

void cmdMul(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double result = (operands[0] * operands[1]) / 100.0;  // Normalize product to keep within 0-100 range
        std::cout << "Result (MULTIPLY): " << result << std::endl;
    }
}

void cmdDiv(double* operands, int numOperands) {
    if (numOperands >= 2 && operands[1] != 0) {
        double result = (operands[0] / operands[1]) * 100;  // Normalize division to keep within 0-100 range
        std::cout << "Result (DIVIDE): " << result << std::endl;
    } else {
        std::cerr << "Error: Division by zero" << std::endl;
    }
}

void cmdEq(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double result = (operands[0] == operands[1]) ? 100 : 0;  // 100 if equal, 0 otherwise
        std::cout << "Result (EQUALS): " << result << std::endl;
    }
}

void cmdDNE(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double result = (operands[0] != operands[1]) ? 100 : 0;  // 100 if not equal, 0 otherwise
        std::cout << "Result (DOES NOT EQUAL): " << result << std::endl;
    }
}

void cmdGT(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double result = (operands[0] > operands[1]) ? 100 : 0;  // 100 if greater, 0 otherwise
        std::cout << "Result (GREATER THAN): " << result << std::endl;
    }
}

void cmdLT(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double result = (operands[0] < operands[1]) ? 100 : 0;  // 100 if less, 0 otherwise
        std::cout << "Result (LESS THAN): " << result << std::endl;
    }
}

void cmdGTE(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double result = (operands[0] >= operands[1]) ? 100 : 0;  // 100 if greater or equal, 0 otherwise
        std::cout << "Result (GREATER THAN OR EQUAL): " << result << std::endl;
    }
}

void cmdLTE(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double result = (operands[0] <= operands[1]) ? 100 : 0;  // 100 if less or equal, 0 otherwise
        std::cout << "Result (LESS THAN OR EQUAL): " << result << std::endl;
    }
}

void cmdAnd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double result = std::min(operands[0], operands[1]);  // Fuzzy AND: MIN function
        std::cout << "Result (AND): " << result << std::endl;
    }
}

void cmdOr(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double result = std::max(operands[0], operands[1]);  // Fuzzy OR: MAX function
        std::cout << "Result (OR): " << result << std::endl;
    }
}

void cmdXor(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double result = std::fabs(operands[0] - operands[1]);  // Fuzzy XOR: Absolute difference
        std::cout << "Result (XOR): " << result << std::endl;
    }
}

void cmdNot(double* operands, int numOperands) {
    if (numOperands >= 1) {
        double result = 100 - operands[0];  // Fuzzy NOT: Inversion
        std::cout << "Result (NOT): " << result << std::endl;
    }
}

void cmdNand(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double andResult = std::min(operands[0], operands[1]);
        double result = 100 - andResult;  // Fuzzy NAND: NOT of AND
        std::cout << "Result (NAND): " << result << std::endl;
    }
}

void cmdNor(double* operands, int numOperands) {
    if (numOperands >= 2) {
        double orResult = std::max(operands[0], operands[1]);
        double result = 100 - orResult;  // Fuzzy NOR: NOT of OR
        std::cout << "Result (NOR): " << result << std::endl;
    }
}

void cmdIf(double* operands, int numOperands) {
    if (numOperands >= 3) {
        double result = (operands[0] > 0) ? operands[1] : operands[2];  // Fuzzy IF: Conditional selection
        std::cout << "Result (IF): " << result << std::endl;
    }
}

// Helper functions for fuzzy logic
void cmdThen(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (THEN): " << clamp(operands[0] ? operands[1] : 0) << std::endl;
    }
}

void cmdElse(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (ELSE): " << clamp(operands[0]) << std::endl;
    }
}

void cmdWhile(double* operands, int numOperands) {
    if (numOperands >= 2) {
        while (operands[0] > 0) {
            std::cout << "Executing (WHILE) with operand: " << clamp(operands[0]) << std::endl;
            operands[0]--;  // Example loop decrement
        }
    }
}

void cmdFor(int start, int end, int step, std::function<void(int)> body) {
    for (int i = start; i < end; i += step) {
        body(i);
    }
}

void cmdBuf(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BUFFER): " << clamp((operands[0] = operands[1])) << std::endl;
    }
}

void cmdInhibit(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (INHIBIT): " << clamp((operands[0] = operands[0])) << std::endl;
    }
}

void cmdEquiv(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (EQUIV): " << clamp(operands[0] == operands[1] ? 100 : 0) << std::endl;
    }
}

void cmdId(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (IDENTITY): " << clamp(operands[0]) << std::endl;
    }
}

void cmdBool(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (BOOLEAN): " << (operands[0] != 0 ? "true" : "false") << std::endl;
    }
}

void cmdBin2Fuz(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (BINARY-2-FUZZY): " << clamp(100 - operands[0]) << std::endl;
    }
}

void cmdFuz2Bin(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (FUZZY-2-BINARY): " << clamp(operands[0] * 1.0) << std::endl;  // Assuming fuzzy value is already in [0, 100]
    }
}

void cmdVectAdd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (VECTOR ADD): " << clamp(operands[0] + operands[1]) << std::endl;
    }
}

void cmdVectSub(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (VECTOR SUB): " << clamp(operands[0] - operands[1]) << std::endl;
    }
}

void cmdDotProd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (DOT PRODUCT): " << clamp(operands[0] * operands[1]) << std::endl;
    }
}

void cmdMtrxDet(double* operands, int numOperands) {
    if (numOperands >= 2) {
        // Example operation, replace with actual matrix determinant calculation
        std::cout << "Result (MATRIX DET): " << clamp(operands[0] * operands[1]) << std::endl;
    }
}

void cmdMtrxInv(double* operands, int numOperands) {
    if (numOperands >= 2) {
        // Example operation, replace with actual matrix inversion calculation
        std::cout << "Result (MATRIX INV): " << clamp(operands[0] / operands[1]) << std::endl;
    }
}

void cmd3x3Det(double* operands, int numOperands) {
    if (numOperands >= 2) {
        // Example operation, replace with actual 3x3 matrix determinant calculation
        std::cout << "Result (3X3 DET): " << clamp(operands[0] * operands[1]) << std::endl;
    }
}

void cmdMtrxAnd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        // Example operation, replace with actual matrix AND calculation
        std::cout << "Result (MATRIX AND): " << clamp(operands[0] && operands[1]) << std::endl;
    }
}

void cmdBreak(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BREAK): " << clamp(operands[0]) << std::endl;
    }
}

void cmdEnd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (END): " << clamp(operands[0]) << std::endl;
    }
}

void cmdExit(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (EXIT): " << clamp(operands[0]) << std::endl;
    }
}

void cmdPrompt(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (PROMPT): " << clamp(operands[0]) << std::endl;
    }
}

void cmdDone(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (DONE): " << clamp(operands[0]) << std::endl;
    }


void cmdHttpGet(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (HTTP GET): " << clamp(operands[0]) << std::endl;
    }
}

void cmdProxy(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (PROXY): " << clamp(operands[0]) << std::endl;
    }
}

void cmdHttp?(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (HTTP): " << clamp(operands[0]) << std::endl;
    }
}

void cmdGetProxy(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (GETPROXY): " << clamp(operands[0]) << std::endl;
    }
}

void cmdServer(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (SERVER): " << clamp(operands[0]) << std::endl;
    }
}

void cmdUserAgent(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (USER AGENNT): " << clamp(operands[0]) << std::endl;
    }

}
void cmdFnct(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (FUNCTION): " << clamp(operands[0]) << std::endl;
    }
}

void cmdAttribute(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (ATTRIBUTE): " << clamp(operands[0]) << std::endl;
    }
}

void cmdType(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (TYPE): " << clamp(operands[0]) << std::endl;
    }
}

void cmdWait(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (WAIT): " << clamp(operands[0]) << std::endl;
    }
}

void cmdSleep(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (SLEEP): " << clamp(operands[0]) << std::endl;
    }
}

void cmdPrint(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (PRINT): " << clamp(operands[0]) << std::endl;
    }
}


// Utility function to clamp values to the range [0, 100]
double clamp(double value) {
    return std::max(0.0, std::min(100.0, value));
}

// Helper functions for fuzzy logic
void cmdThen(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (THEN): " << clamp(operands[0] ? operands[1] : 0) << std::endl;
    }
}

void cmdElse(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (ELSE): " << clamp(operands[0]) << std::endl;
    }
}

void cmdWhile(double* operands, int numOperands) {
    if (numOperands >= 2) {
        while (operands[0] > 0) {
            std::cout << "Executing (WHILE) with operand: " << clamp(operands[0]) << std::endl;
            operands[0]--;  // Example loop decrement
        }
    }
}

void cmdFor(int start, int end, int step, std::function<void(int)> body) {
    for (int i = start; i < end; i += step) {
        body(i);
    }
}

void cmdBuf(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BUFFER): " << clamp((operands[0] = operands[1])) << std::endl;
    }
}

void cmdInhibit(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (INHIBIT): " << clamp((operands[0] = operands[0])) << std::endl;
    }
}

void cmdEquiv(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (EQUIV): " << clamp(operands[0] == operands[1] ? 100 : 0) << std::endl;
    }
}

void cmdId(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (IDENTITY): " << clamp(operands[0]) << std::endl;
    }
}

void cmdBool(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (BOOLEAN): " << (operands[0] != 0 ? "true" : "false") << std::endl;
    }
}

void cmdBin2Fuz(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (BINARY-2-FUZZY): " << clamp(100 - operands[0]) << std::endl;
    }
}

void cmdFuz2Bin(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (FUZZY-2-BINARY): " << clamp(operands[0]) << std::endl;  // Assuming fuzzy value is already in [0, 100]
    }
}

void cmdVectAdd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (VECTOR ADD): " << clamp(operands[0] + operands[1]) << std::endl;
    }
}

void cmdVectSub(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (VECTOR SUB): " << clamp(operands[0] - operands[1]) << std::endl;
    }
}

void cmdDotProd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (DOT PRODUCT): " << clamp(operands[0] * operands[1]) << std::endl;
    }
}

void cmdMtrxDet(double* operands, int numOperands) {
    if (numOperands >= 2) {
        // Example operation, replace with actual matrix determinant calculation
        std::cout << "Result (MATRIX DET): " << clamp(operands[0] * operands[1]) << std::endl;
    }
}

void cmdMtrxInv(double* operands, int numOperands) {
    if (numOperands >= 2) {
        // Example operation, replace with actual matrix inversion calculation
        std::cout << "Result (MATRIX INV): " << clamp(operands[0] / operands[1]) << std::endl;
    }
}

void cmd3x3Det(double* operands, int numOperands) {
    if (numOperands >= 2) {
        // Example operation, replace with actual 3x3 matrix determinant calculation
        std::cout << "Result (3X3 DET): " << clamp(operands[0] * operands[1]) << std::endl;
    }
}

void cmdMtrxAnd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        // Example operation, replace with actual matrix AND calculation
        std::cout << "Result (MATRIX AND): " << clamp(operands[0] && operands[1] ? 100 : 0) << std::endl;
    }
}

void cmdBreak(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BREAK): " << clamp(operands[0]) << std::endl;
    }
}

void cmdEnd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (END): " << clamp(operands[0]) << std::endl;
    }
}

void cmdExit(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (EXIT): " << clamp(operands[0]) << std::endl;
    }
}

void cmdPrompt(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (PROMPT): " << clamp(operands[0]) << std::endl;
    }
}

void cmdDone(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (DONE): " << clamp(operands[0]) << std::endl;
    }
}

void cmdHttp(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (HTTP): " << clamp(operands[0]) << std::endl;
    }
}

void cmdProxy(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (PROXY): " << clamp(operands[0]) << std::endl;
    }
}

void cmdGetProxy(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (GET PROXY): " << clamp(operands[0]) << std::endl;
    }
}

void cmdServer(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (SERVER): " << clamp(operands[0]) << std::endl;
    }
}

void cmdUser(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (USER): " << clamp(operands[0]) << std::endl;
    }
}

void cmdAgent(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (AGENT): " << clamp(operands[0]) << std::endl;
    }
}

void cmdFnct(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (FUNCTION): " << clamp(operands[0]) << std::endl;
    }
}

void cmdAttribute(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (ATTRIBUTE): " << clamp(operands[0]) << std::endl;
    }
}

void cmdType(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (TYPE): " << clamp(operands[0]) << std::endl;
    }
}

void cmdWait(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (WAIT): " << clamp(operands[0]) << std::endl;
    }
}

void cmdSleep(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (SLEEP): " << clamp(operands[0]) << std::endl;
    }
}

void cmdPrint(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (PRINT): " << clamp(operands[0]) << std::endl;
    }
}

void cmdChar(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (CHAR): " << clamp(operands[0]) << std::endl;
    }
}

void cmdRead(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (READ): " << clamp(operands[0]) << std::endl;
    }
}

void cmdMove(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (MOVE): " << clamp(operands[0]) << std::endl;
    }
}

void cmdNull(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (NULL): " << clamp(operands[0]) << std::endl;
    }
}

void cmdPath(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (PATH): " << clamp(operands[0]) << std::endl;
    }
}


void cmdHttpGet(const std::string& url) {
    CURL* curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}


// Complete all the command functions similarly...

void cmdHttpGet(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::string url = std::to_string(operands[0]); // Convert operand to string URL
        CURL* curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
    }
}

// Main function to execute commands based on type
void executeCommand(CommandType commandType, double* operands, int numOperands) {
    auto it = commandMap.find(commandType);
    if (it != commandMap.end()) {
        it->second(operands, numOperands);
    } else {
        std::cerr << "Unknown command" << std::endl;
    }
}

int main() {
    double operands[] = {5.0, 3.0};
    int numOperands = 2;

    executeCommand(CMD_ADD, operands, numOperands); // Example usage
    executeCommand(CMD_DIV, operands, numOperands);

    return 0;
}
