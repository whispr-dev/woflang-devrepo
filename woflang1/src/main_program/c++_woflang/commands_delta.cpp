// `commmand_beta.cpp` woflang interpreter/parser alter

#include "commands.h"
#include <iostream>
#include <unordered_map>
#include <functional>
#include <cmath>       // For mathematical operations
#include <bitset>      // For bitwise operations
#include <cstring>     // For memcpy
#include <curl/curl.h>
#include <cstdlib>     // For setenv

// Enum for command types
enum CommandType {
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

// Map command types to their functions
std::unordered_map<CommandType, CommandFunction> commandMap = {
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
    {CMD_ONE, cmdDone},
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

// Function to copy and concatenate strings
void cmdStrCopy(char* dest, const char* src1, const char* src2) {
    std::strcpy(dest, src1);
    std::strcat(dest, src2);
}


// Implementing various command functions

void cmdCmp(double& result, double a, double b) {
    if (a > b) {
        result = 1;  // Set result to 1 if 'a' is greater than 'b'
    } else {
        result = 0;  // Set result to 0 otherwise
    }
}

void cmdAdd(double& result, double a, double b) {
    result = a + b;
}

void cmdSub(double& result, double a, double b) {
    result = a - b;
}

void cmdMul(double& result, double a, double b) {
    result = a * b;
}

void cmdDiv(double& result, double a, double b) {
    if (b != 0) {
        result = a / b;
    } else {
        std::cerr << "Error: Division by zero\n";
    }
}

void cmdEq(double& result, double a, double b) {
    result = (a == b);
}


void cmdDNE(double& result, double a, double b) {
    result = (a != b);
}

void cmdGT(double& result, double a, double b) {
    result = (a > b);
}

void cmdLT(double& result, double a, double b) {
    result = (a < b);
}

void cmdGTE(double& result, double a, double b) {
    result = (a >= b);
}

void cmdLTE(double& result, double a, double b) {
    result = (a <= b);
}

void cmdAnd(int& result, int a, int b) {
    result = a & b;
}

void cmdOr(int& result, int a, int b) {
    result = a | b;
}

void cmdXor(int& result, int a, int b) {
    result = a ^ b;
}

void cmdNot(int& result, int a) {
    result = ~a;
}

void cmdNand(int& result, int a, int b) {
    result = ~(a & b);
}

void cmdNor(int& result, int a, int b) {
    result = ~(a | b);
}
void cmdIf(int& result, int condition, int trueVal, int falseVal) {
    result = condition ? trueVal : falseVal;
}

void cmdThen(int& result, int condition, int value) {
    if (condition) {
        result = value;
    }
}
void cmdElse(int& result) {
    result = 0;
}
void cmdWhile(std::function<bool()> condition, std::function<void()> body) {
    while (condition()) {
        body();
    }
}

void cmdFor(int start, int end, int step, std::function<void(int)> body) {
    for (int i = start; i < end; i += step) {
        body(i);    

void cmdBuf(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BUFFER): " << (operands[0] = operands[1]) << std::endl;
    }
}

void cmdInhibit(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (INHIBIT): " << (operands[0] = operands[0]) << std::endl;
    }
}

void cmdEquiv(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (EQUIV): " << (operands[0] = operands[1]) << std::endl;
    }
}

void cmdId(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (IDENTITY): " << (operands[1] = operands[1]) << std::endl;
    }
}

void cmdBin2Fuz(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BINARY-2-FUZZY): " << (operands[0] = 100 - operands[1]) << std::endl;
    }
}

void cmdFuz2Bin(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (FUZZY-2-BINARY): " << (operands[0] = (operands[1]/ 2 *)0.1) << std::endl;
    }
}

void cmdBool(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BOOLEAN): " << (operands[0] = operands[1]) << std::endl;
            return = true
            else if result  = 0, return false
    }
}

void cmdVectAdd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (VECTOR ADD): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdVectSub(int& result) {
    if (numOperands >= 2) {
        std::cout << "Result (VECTOR SUB): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdDotProd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (DOT  PRODUCT): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdMtrxDet(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (MATRIX DET): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdMtrxInv(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (MATRIX INV): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd3x3Det(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (3X3 DET): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdMtrxAnd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (MATRIX AND): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BREAK): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (END): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (EXIT): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (PROMPT): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (DONE): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Http): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Proxy): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Http): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (GetProxy): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Server): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (User): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Agent): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Fnct): " << (operands[0] <= operands[1]) << std::endl;
    }
}


void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Attribute): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Type): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Wait): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Sleep): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Print): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Char): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Read): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Move): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Null): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Path): " << (operands[0] <= operands[1]) << std::endl;
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
