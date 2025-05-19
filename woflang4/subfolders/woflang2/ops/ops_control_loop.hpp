// ops_control_loop.hpp
// WOFLANG loop and control flow opcodes: loop, repeat, for, break, continue

#pragma once
#include "wof_interpreter.hpp"
#include <iostream>

// Opcode constants (assign these in your glyphmap):
// ⟳ = loop         → opcode 201
// ⨯ = repeat       → opcode 202
// ⍺ = for          → opcode 203
// 🛑 = break        → opcode 204
// ↻ = continue     → opcode 205

void register_loop_opcodes(WofInterpreter& vm) {
    // ⟳ Infinite loop
    vm.registerOpcode(201, [](WofInterpreter& vm, const WofToken& token) {
        std::cout << "[loop] ⟳ enter loop block at IP " << token.position << "\n";
        // Push loop metadata on blockStack: type="loop", start=IP, etc.
        // Run loop block until break
    });

    // ⨯ Repeat N times (N on stack)
    vm.registerOpcode(202, [](WofInterpreter& vm, const WofToken& token) {
        int64_t count = vm.pop();
        std::cout << "[repeat] ⨯ repeating " << count << " times from IP " << token.position << "\n";
        // Push loop block with counter, decrement each run, break when 0
    });

    // ⍺ For loop (start, end, step on stack)
    vm.registerOpcode(203, [](WofInterpreter& vm, const WofToken& token) {
        int64_t step = vm.pop();
        int64_t end  = vm.pop();
        int64_t start = vm.pop();
        std::cout << "[for] ⍺ from " << start << " to " << end << " step " << step << "\n";
        // Set up for loop counter and track i per iteration
    });

    // 🛑 Break out of loop
    vm.registerOpcode(204, [](WofInterpreter& vm, const WofToken& token) {
        std::cout << "[break] Breaking out of loop at IP " << token.position << "\n";
        // Find nearest loop block, override instruction pointer to ⺘
    });

    // ↻ Continue to next iteration
    vm.registerOpcode(205, [](WofInterpreter& vm, const WofToken& token) {
        std::cout << "[continue] Jumping to next loop iteration\n";
        // Set instructionPointerOverride to start of block
    });
}
