// wof_loop_iterator_variable_patch.cpp
// Implements loop iterator variable exposure in ⍺ (for) loops

#include "wof_interpreter.hpp"
#include <iostream>

void register_for_loop_iterator_patch(WofInterpreter& vm) {
    vm.registerOpcode(203, [](WofInterpreter& vm, const WofToken& token) {
        int64_t step  = vm.pop();
        int64_t end   = vm.pop();
        int64_t start = vm.pop();

        size_t blockStart = token.position;
        size_t blockEnd = vm.findBlockEnd(blockStart);

        if ((step > 0 && start > end) || (step < 0 && start < end)) {
            vm.instructionPointerOverride = blockEnd;  // skip block
            return;
        }

        // Create iterator and assign to scope
        std::string loopVar = "i"; // hardcoded for now
        if (!vm.scopeStack.empty()) {
            vm.scopeStack.top()[loopVar] = start;
        }

        // Push loop frame (⍺ type with end/step + IP range)
        LoopFrame frame{blockStart, blockEnd, end, "for"};
        vm.loopContext.push(frame);
        vm.instructionPointerOverride = blockStart + 1;
    });

    // Patch ↻ to advance iterator
    vm.registerOpcode(205, [](WofInterpreter& vm, const WofToken&) {
        auto opt = vm.loopContext.current();
        if (!opt.has_value()) return;

        auto& frame = opt.value();
        if (frame.type != "for") {
            vm.loopContext.continueLoop(vm.instructionPointerOverride.emplace(0));
            return;
        }

        std::string loopVar = "i";
        auto& scope = vm.scopeStack.top();
        int64_t i = scope[loopVar];
        int64_t end = frame.counter.value();  // target
        int64_t step = 1; // assumed default

        if ((step > 0 && i + step > end) || (step < 0 && i + step < end)) {
            vm.loopContext.pop(); // exit loop
            vm.instructionPointerOverride = frame.endIP;
        } else {
            scope[loopVar] = i + step;
            vm.instructionPointerOverride = frame.startIP + 1;
        }
    });
}
