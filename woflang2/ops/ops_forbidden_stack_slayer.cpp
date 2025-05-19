// ops_forbidden_stack_slayer.cpp
// Implements ☠ forbidden opcode to wipe the stack

#pragma once
#include "wof_interpreter.hpp"
#include <iostream>

void register_forbidden_stack_slayer(WofInterpreter& vm) {
    vm.registerOpcode(3999, [](WofInterpreter& vm, const WofToken&) {
        if (!vm.secretsUnlocked) {
            std::cout << "[☠] Access denied. Chaos glyph locked.\n";
            return;
        }
        while (!vm.valueStack.empty()) vm.valueStack.pop();
        std::cout << "[☠] The stack has been slain.\n";
    });
}
