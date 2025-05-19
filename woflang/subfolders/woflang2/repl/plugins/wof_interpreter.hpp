#pragma once

#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <iostream>

struct WofValue {
    enum Type { INT, LIST };
    Type type;
    int64_t intVal;
    std::vector<WofValue> listVal;
};

struct LoopFrame {
    size_t startIP;
    size_t endIP;
    int64_t counter;
    std::string type;
};

class BlockRegistry; // forward declarations
class KeyBindingManager;

class WofInterpreter {
public:
    std::vector<WofValue> valueStack;
    std::stack<LoopFrame> loopStack;
    BlockRegistry* blockRegistry;
    KeyBindingManager* keybinds;
    bool secretsUnlocked = false;

    void push(int64_t val);
    void pushValue(const WofValue& val);
    WofValue popValue();

    void execute(const std::u32string& code);
    void loadPlugin(const std::string& path);
    void findBlockEnd();

    // Add more as needed
};

