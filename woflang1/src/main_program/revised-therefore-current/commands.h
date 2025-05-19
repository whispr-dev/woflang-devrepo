// commands.h

#pragma once
#include <unordered_map>
#include <functional>

// Define CommandType enum at the top
enum CommandType {
    CMD_CMP = 0x4C,
    CMD_ADD = 0x01,
    CMD_SUB = 0x02,
    CMD_MUL = 0x03,
    CMD_DIV = 0x04,
    CMD_GT = 0x05,
    CMD_LT = 0x06,
    CMD_EQ = 0x07,
    CMD_DNE = 0x08,
    CMD_GTE = 0x09,
    CMD_LTE = 0x0A,
    CMD_AND = 0x0B,
    CMD_OR = 0x0C,
    CMD_XOR = 0x0D,
    CMD_NOT = 0x0E,
    CMD_NAND = 0x0F,
    CMD_NOR = 0x10,
    CMD_IF = 0x11,
    CMD_THEN = 0x12,
    CMD_ELSE = 0x13,
    CMD_WHILE = 0x14,
    CMD_FOR = 0x15,
    CMD_BUF = 0x16,
    CMD_INHIBIT = 0x17,
    CMD_EQUIV = 0x18,
    CMD_ID = 0x19,
    CMD_BIN2FUZ = 0x1A,
    CMD_FUZ2BIN = 0x1B,
    CMD_BOOL = 0x1C,
    CMD_COUNT = 0x1D,
    CMD_STR = 0x1E,
    CMD_VECTADD = 0x1F,
    CMD_VECTSUB = 0x20,
    CMD_DOTPROD = 0x21,
    CMD_MTRXDET = 0x22,
    CMD_MTRXINV = 0x23,
    CMD_3X3DET = 0x24,
    CMD_MTRXAND = 0x25,
    CMD_BREAK = 0x26,
    CMD_END = 0x27,
    CMD_EXIT = 0x28,
    CMD_PROMPT = 0x29,
    CMD_DONE = 0x2A,
    CMD_PROXY = 0x2C,
    CMD_GETPROXY = 0x2D,
    CMD_SERVER = 0x2E,
    CMD_USERAGENT = 0x2F,
    CMD_FNCT = 0x30,
    CMD_ATTRIBUTE = 0x31,
    CMD_TYPE = 0x32,
    CMD_WAIT = 0x33,
    CMD_SLEEP = 0x34,
    CMD_PRINT = 0x35,
    CMD_CHAR = 0x36,
    CMD_READ = 0x37,
    CMD_MOVE = 0x38,
    CMD_NULL = 0x39,
    CMD_PATH = 0x3A,
    CMD_STARTSERVER = 0x3D,
    CMD_STOPSERVER = 0x3E,
    CMD_SETATTRIBUTE = 0x3F,
    CMD_SETPROXY = 0x40,
    CMD_IMPLY = 0x43,
    CMD_NIMPLY = 0x44,
    CMD_INHIBITXY = 0x46,
    CMD_BUFFER = 0x47,
    CMD_IMPLICATION = 0x4A,
    CMD_IDENTITY = 0x4B,
    CMD_EQUIVALENCE = 0x49,
};

typedef std::function<void(double*, int)> CommandFunction;
extern std::unordered_map<CommandType, CommandFunction> commandMap;

// Add the rest of your function declarations
void executeCommand(CommandType command, double* operands, int numOperands);
void cmdStartServer(double* operands, int numOperands);
void cmdStopServer(double* operands, int numOperands);
// Other function declarations...
