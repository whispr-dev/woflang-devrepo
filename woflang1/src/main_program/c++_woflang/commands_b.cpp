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
    CMD_CMP
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
    CMD_NAND
    CMD_NOR,
    CMD_IF,
    CMD_THEN,
    CMD_ELSE
    CMD_WHILE
    CMD_FOR
    CMD_EXCEPT
    CMD_IMPLY
    CMD_NIMPLY
    CMD_INHIBIT
    CMD_BUF
    CMD_INHIBIT_XY
    CMD_EQUIV
    CMD_IDENTITY
    CMD_BIN2FUZZ
    CMD_FUZZ2BIN
    CMD_BOOL
    COUNT
    STR
    VECTADD
    VECTSUB
    DOTPROD
    MTRXDET
    MTRXINV
    3X3DET
    MTRXAND
    BREAK
    END
    DONE
    EXIT
    PROMPT
    INPUT
    SYS
    ECHO
    HTTP
    PROXY
    USER
    FUNCTION
    ATTRIBUTE
    USER
    TYPE
    SERVER
    WAIT
    SLEEP
    PRINT
    CHAR
    READ
    MOVE
    NULL
    PATH


void cmdStrCopy(char* dest, const char* src1, const char* src2) {
    std::strcpy(dest, src1);
    std::strcat(dest, src2);
}
void cmdCount(const char* str, int& count) {
    count = std::strlen(str);
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


void setHttpProxy(const std::string& proxy) {
    setenv("http_proxy", proxy.c_str(), 1);
}

void setHttpsProxy(const std::string& proxy) {
    setenv("https_proxy", proxy.c_str(), 1);
}




    
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

void cmdEq (double& result, double a, double b )
    result = a = b;
}

void cmdDNE (double& result, double a, double b )
    result = a!=  b;
}

void cmdGT (double& result, double a, double b )
    result = a >  b;
}

void cmdLT (double& result, double a, double b )
    result = a <  b;
}

void cmdGTE (double& result, double a, double b )
    result = a >=b;
}

void cmdLTE(double& result, double a, double b )
    result = a <= b;
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
}
void cmdBuf(int& result) {
    result = value;

}
void cmdInhibit(int& result) {
    result = 0;

}
void cmdEquiv(int& result) {
    result = ;

}
void cmdId(int& result) {
    result = 0;
}
void cmdBin2Fuz(int& result) {
    result = 0;

}
void cmdFuz2Bin(int& result) {
    result = 0;

}
void cmdBool(int& result) {
    result = 0;

}
void cmdCount(int& result) {
    result = 0;
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
void cmdHttp(int& result) {
    result = 0;

}
void cmdProxy(int& result) {
    result = 0;

}
void cmdUser(int& result) {
    result = 0;

}
void cmdnctn(int& result) {
    result = 0;F

}
void cmdAttribute(int& result) {
    result = 0;

}
void cmdType(int& result) {
    result = 0;

}
void cmdServer(int& result) {
    result = 0;S

}
void cmdWait(int& result) {
    result = 0;

}
void cmdSleep(int& result) {
    result = 0

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


// Command execution functions
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

void cmdAdd(double* operands, int numOperands) {
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

// Map command types to their functions
std::


// alt way to clc:
    switch (command) {
        case CMD_ CMP:
            if (numOperands >= 2) {
                result = operands[0]  operands[1];
            }
            break;
        case CMD_ADD:
            if (numOperands >= 2) {
                result = operands[0] + operands[1];
            }
            break;
        case CMD_SUB:
           if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_MUL:
           if (numOperands >= 2) {
               result = operands[0] * operands[1];
           }
           break;
        case CMD_DIV
           if (numOperands >= 2) {
               result = operands[0] / operands[1];
           }
           break;
        case CMD_EQ:
           if (numOperands >= 2) {
               result = operands[0] = operands[1];
           }
           break;
        case CMD_DNE:
           if (numOperands >= 2) {
               result = operands[0] != operands[1];
           }
           break;
        case CMD_GT:
           if (numOperands >= 2) {
               result = operands[0] > operands[1];
           }
           break;
        case CMD_LT:
           if (numOperands >= 2) {
               result = operands[0] <operands[1];
           }
           break;        
        case CMD_GTE:
           if (numOperands >= 2) {
               result = operands[0] >= operands[1];
           }
           break;
        case CMD_LTE:
           if (numOperands >= 2) {
               result = operands[0] <= operands[1];
           }
           break;
        case CMD_AND:
           if (numOperands >= 2) {
               result = operands[0] * operands[1];
           }
           break;
        case CMD_OR:
           if (numOperands >= 2) {
               result = operands[0] + operands[1];
           }
           break;
        case CMD_XOR:
           if (numOperands >= 2) {
               result = operands[0] xor operands[1];
           }
           break;
        case CMD_NOT:
           if (numOperands >= 2) {
               result = operands[0] = - operands[0];
           }
           break;
        case CMD_NAND:
           if (numOperands >= 2) {
               result = - operands[0] * (operands[1]);
           }
           break;
        case CMD_NOR:
           if (numOperands >= 2) {
               result = - operands[0] + operands[1];
           }
           break;
        case CMD_IF:
           if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_ THEN:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_ ELSE:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_WHILE:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_FOR:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_EXCEPT:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_IMPLY:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_NIMPLY:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_INHIBIT:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_BUFFER:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_INHIBIT_XY:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_EQUIVAL:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_IMPLY:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_IDENTITY:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_BIN2FUZZY:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_FUZZ#Y2BIN:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_BOOL:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_COUNT:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_STR:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break;
        case CMD_VECTADD:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case CMD_VECTSUB:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:                       
        case DOTPROD:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case MTRXDET:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case MTRXINV:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case 3X3DET:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case BREAK:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case END:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case DONE:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case  EXIT:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case  PROMMPT:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case INPUT:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case SYS:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case ECHO:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case HTTP:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case PROXY:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case USERAGENT:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case FUNCTION:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:               
        case ATTRIBUTE:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case USER:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case  TYPE:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case SERVER:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case WAIT:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case SLEEP:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case PRINT:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:       
        case CHAR:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:     
        case READ:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:        
        case MOVE:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:            
        case NULL:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:                     
        case PATH:
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:         
        case :
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:
        case :
            if (numOperands >= 2) {
               result = operands[0] - operands[1];
           }
           break:

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
