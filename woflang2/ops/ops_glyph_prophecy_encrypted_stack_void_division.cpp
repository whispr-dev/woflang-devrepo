// ops_glyph_prophecy_encrypted_stack_void_division.cpp
// Implements ⌬ (stack encrypt) and ⊘ (division by void) glyph ops

#pragma once
#include "wof_interpreter.hpp"
#include <iostream>
#include <random>

void register_prophetic_glyphs(WofInterpreter& vm) {
    // ⊘ division by emptiness
    vm.registerOpcode(4040, [](WofInterpreter& vm, const WofToken&) {
        int64_t val = vm.pop();
        std::cout << "[⊘] Attempted to divide " << val << " by void..." << std::endl;
        vm.push(0);  // or a NaN sentinel, or remove entirely
    });

    // ⌬ encrypt stack (simple XOR mask)
    vm.registerOpcode(4041, [](WofInterpreter& vm, const WofToken&) {
        if (!vm.secretsUnlocked) {
            std::cout << "[⌬] Encrypted functions are sealed. Use :unlock chaos.\n";
            return;
        }

        std::stack<WofValue> temp;
        while (!vm.valueStack.empty()) {
            WofValue v = vm.valueStack.top(); vm.valueStack.pop();
            if (v.type == WofValue::Type::INT) {
                v.intVal ^= 0x5A5A5A5A;
            }
            temp.push(v);
        }

        while (!temp.empty()) {
            vm.valueStack.push(temp.top()); temp.pop();
        }

        std::cout << "[⌬] Stack encrypted with XOR sigil.\n";
    });
}
