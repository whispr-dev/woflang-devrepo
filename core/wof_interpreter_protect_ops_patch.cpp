// wof_interpreter_protect_ops_patch.cpp
// Enforces opcode protection flag (🧿)

#pragma once
#include <unordered_map>
#include <functional>
#include "wof_value.hpp"

class WofInterpreter {
public:
    std::unordered_map<uint16_t, std::function<void(WofInterpreter&, const WofToken&)>> handlers;
    std::stack<WofValue> valueStack;

    bool protectOps = false;
    bool secretsUnlocked = false;

    void registerOpcode(uint16_t opcode, std::function<void(WofInterpreter&, const WofToken&)> handler) {
        if (protectOps) {
            std::cout << "[🧿] Opcode registration denied: glyph sanctum is sealed.\n";
            return;
        }
        handlers[opcode] = std::move(handler);
    }

    void push(int64_t val) {
        valueStack.push(WofValue(val));
    }

    // other members...
};
