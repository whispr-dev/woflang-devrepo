// ops_control_loop_integrated.hpp
// Finalized loop opcodes using LoopContext

#pragma once
#include "wof_interpreter.hpp"
#include <iostream>

void register_loop_opcodes(WofInterpreter& vm) {
    // ⟳ Infinite loop
    vm.registerOpcode(201, [](WofInterpreter& vm, const WofToken& token) {
        size_t blockStart = token.position;
        size_t blockEnd = vm.findBlockEnd(blockStart);  // assumes such method exists
        LoopFrame frame{blockStart, blockEnd, std::nullopt, "loop"};
        vm.loopContext.push(frame);
        vm.instructionPointerOverride = blockStart + 1;  // jump inside
    });

    // ⨯ Repeat N times (N on stack)
    vm.registerOpcode(202, [](WofInterpreter& vm, const WofToken& token) {
        int64_t count = vm.pop();
        size_t blockStart = token.position;
        size_t blockEnd = vm.findBlockEnd(blockStart);
        if (count > 0) {
            LoopFrame frame{blockStart, blockEnd, count, "repeat"};
            vm.loopContext.push(frame);
            vm.instructionPointerOverride = blockStart + 1;
        } else {
            vm.instructionPointerOverride = blockEnd;  // skip block
        }
    });

    // ⍺ For loop (start, end, step on stack)
    vm.registerOpcode(203, [](WofInterpreter& vm, const WofToken& token) {
        int64_t step  = vm.pop();
        int64_t end   = vm.pop();
        int64_t start = vm.pop();
        size_t blockStart = token.position;
        size_t blockEnd = vm.findBlockEnd(blockStart);
        if ((step > 0 && start > end) || (step < 0 && start < end)) {
            vm.instructionPointerOverride = blockEnd;
        } else {
            vm.push(start);
            LoopFrame frame{blockStart, blockEnd, end, "for"};
            vm.loopContext.push(frame);
            vm.instructionPointerOverride = blockStart + 1;
        }
    });

    // 🛑 Break
    vm.registerOpcode(204, [](WofInterpreter& vm, const WofToken& token) {
        vm.loopContext.breakLoop(vm.instructionPointerOverride.emplace(0));
    });

    // ↻ Continue
    vm.registerOpcode(205, [](WofInterpreter& vm, const WofToken& token) {
        vm.loopContext.continueLoop(vm.instructionPointerOverride.emplace(0));
    });
}
