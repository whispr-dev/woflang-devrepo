#include "commands.h"
#include <iostream>
#include <unordered_map>
#include <functional>
#include <cmath>  // For mathematical operations
#include <bitset>  // For bitwise operations
#include <cstring>  // For memcpy
#include <curl/curl.h>
#include <cstdlib>  // For setenv

// Implement each command execution function
// void executeCommand(CommandType command, double* operands, int numOperands) {
//     double result = 0; // Placeholder for result

// Enum for command types
enum CommandType {

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
    ( CMD_COUNT, cmdCount),
    ( CMD_STR, cmdSTR),
     ( CMD_VECTADD, cmdVectAdd),
     ( CMD_VECTSUB, cmdVectSub),
     ( CMD_DOTPROD, cmdDotProd),
     ( CMD_MTRXDET, cmdMtrxDet),
     ( CMD_MTRXINV, cmdMtrxInv),
     ( CMD_3X3DET, cmd3X3Det),
     ( CMD_MTRXAND, cmdMtrxAnd),
     ( CMD_BREAK, cmdBreak),
     ( CMD_END, cmdEnd),
    ( CMD_DONE, cmdDone),
     ( CMD_EXIT, cmdExit),
     ( CMD_PROMPT, cmdPrompt),
     ( CMD_INPUT, cmdInput),
     ( CMD_SYSCALL, cmdSysCall),
     ( CMD_ECHO, cmdEcho),
     ( CMD_HTTP, cmdHttp),
     ( CMD_PROXY, cmdProxy),
     ( CMD_USERAGENT, cmdUserAgent),
     ( CMD_FUNC, cmdFunc),
     ( CMD_ATTRIBUTE, cmdAttribute),
     ( CMD_TYPE, cmdType),
     ( CMD_SERVER, cmdSTR),
     ( CMD_WAIT, cmdWait),
     ( CMD_SLEEP, cmdSleep),
    ( CMD_ PRINT, cmdPrint),
     ( CMD_CHAR, cmdChar),
     ( CMD_READ, cmdRead),
     ( CMD_MOVE, cmdMove),
     ( CMD_NULL, cmdNull),
    ( CMD_PATH, cmdPath),

    // Add more command mappings here
};

void cmdStrCopy(char* dest, const char* src1, const char* src2) {
    std::strcpy(dest, src1);
    std::strcat(dest, src2);
    

    CommandFunction
    // Add more commands as needed
};
// Typedef for function pointer for command execution
typedef std::function<void(double*, int)> CommandFunction;


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
    }

void cmdBuf(int& result) {
    // Buffer logic
    result = input;
}

void cmdInhibit(int& result) {
    // Inhibition logic
    result = 0;
}

void cmdEquiv(int& result) {
    // Equivalence logic
    result = 0;
}

void cmdId(int& result) {
    result = 0;
}

void cmdBin2Fuz(int& result) {
    // Convert binary to fuzzy logic value
    result = 100 - input;
}

void cmdFuz2Bin(int& result) {
    // Convert fuzzy logic to binary
    result = input + (- 100);

}
void cmdBool(int& result) {
    // Boolean logic
    if result = 1 return 'true';
    else result = 0  return 'false' 
}


void cmdCount(const char* str, int& count) {
    count = std::strlen(str);
}

void cmdStr(int& result) {
    result = 0;

}
void cmdVectAdd(int& result) {
    result = 0;

}
void cmdVectSub(int& result) {
    result = 0;

}
void cmdDotProd(int& result) {
    result = 0;

}
void cmdMtrxDet(int& result) {
    result = 0;

}
void cmdMtrxInv(int& result) {
    result = 0;

}
void cmd3x3Det(int& result) {
    result = 0;

}
void cmdMtrxAnd(int& result) {
    result = 0;

}
void cmdBreak(int& result) {
    result = 0;

}
void cmdEnd(int& result) {
    result = 0;

}
void cmdDone(int& result) {
    result = 0;

}
void cmdExit(int& result) {
    result = 0;

}
void cmdPrompt(int& result) {
    result = 0;

}
void cmdInput(int& result) {
    result = 0;

}
void cmdSysCall(int& result) {
    result = 0;

}
void cmdEcho(int& result) {
    result = 0;

}

void setProxy(const std::string& proxy) {
    setenv("http_proxy", proxy.c_str(), 1);
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

void cmdProxy(int& result) {
    result = 0;

}
void cmdServer(int& result) {
    result = 0;S

}
void cmdUserAgent(int& result) {
    result = 0;

}
void cmdFnct(int& result) {
    result = 0;F

}
void cmdAttribute(int& result) {
    result = 0;

}
void cmdType(int& result) {
    result = 0;

}
void cmdWait(int& result) {
    result = 0;

}
void cmdSleep(int& result) {
    result = 0;

}
void cmdPrint(int& result) {
    result = 0;

}
void cmdChar(int& result) {
    result = 0;

}
void cmdRead(int& result) {
    result = 0;

}
void cmdMove(int& result) {
    result = 0;

}
void cmdNull(int& result) {
    result = 0;

}
void cmdPath(int& result) {
    result = 0;



// Command execution functionsvoid cmdAdd(double* operands, int numOperands)

{
    if (numOperands >= 2) {
        std::cout << "Result (CMP): " << operands[0] + operands[1] << std::endl;
    }
}

{
    if (numOperands >= 2) {
        std::cout << "Result (ADD): " << operands[0] + operands[1] << std::endl;
    }
}

void cmdSubtract(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (SUBTRACT): " << operands[0] - operands[1] << std::endl;
    }
}

void cmdMultiply(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (MULTIPLY): " << operands[0] * operands[1] << std::endl;
    }
}

void cmdDivide(double* operands, int numOperands) {
    if (numOperands >= 2 && operands[1] != 0) {
        std::cout << "Result (DIVIDE): " << operands[0] / operands[1] << std::endl;
    } else {
        std::cerr << "Error: Division by zero" << std::endl;
    }
}

void cmdEquals(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (EQUALS): " << (operands[0] == operands[1]) << std::endl;
    }
}

void cmdDoesNotEqual(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (DOES NOT EQUAL): " << (operands[0] != operands[1]) << std::endl;
    }
}

void cmdGreater(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (GREATER): " << (operands[0] > operands[1]) << std::endl;
    }
}

void cmdLess(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (LESS): " << (operands[0] < operands[1]) << std::endl;
    }
}

void cmdGreaterThanEquals(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (GREATER THAN EQUALS): " << (operands[0] >= operands[1]) << std::endl;
    }
}

void cmdLessThanEquals(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (LESS THAN EQUALS): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdAnd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (AND): " << static_cast<int>(operands[0]) & static_cast<int>(operands[1]) << std::endl;
    }
}

void cmdOr(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (OR): " << static_cast<int>(operands[0]) | static_cast<int>(operands[1]) << std::endl;
    }
}

void cmdXor(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (XOR): " << static_cast<int>(operands[0]) ^ static_cast<int>(operands[1]) << std::endl;
    }
}

void cmdNot(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (NOT): " << ~static_cast<int>(operands[0]) << std::endl;
    }
}

void cmdNand(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (NAND): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdNor(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (NOR): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdIf(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (IF): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdThen(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (THEN): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdElse(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (ELSE): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdFor(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (FOR): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdWhile(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (WHILE): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdBuf(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BUFFER): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdInhibit(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (INHIBIT): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdEquiv(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (EQUIV): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdId(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (IDENTITY): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdBin2Fuz(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BINARY-2-FUZZY): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdFuz2Bin(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (FUZZY-2-BINARY): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdBool(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BOOLEAN): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdVectAdd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Break): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdVectSub(int& result) {
    if (numOperands >= 2) {
        std::cout << "Result (End): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdDotProd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Done): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdMtrxDet(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Exit): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdMtrxInv(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Prompt): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd3x3Det(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Input): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdMtrxAnd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (SysCall): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (Echo): " << (operands[0] <= operands[1]) << std::endl;
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


// Map command types to their functions
std::


// SYMBOL_COMMANDS:

        // Other command cases
        // ...
        default:
            std::cerr << "Unknown command" << std::endl;
            return;
    }

    // Print or handle the result
    std::cout << "Result: " << result << std::endl;
}
