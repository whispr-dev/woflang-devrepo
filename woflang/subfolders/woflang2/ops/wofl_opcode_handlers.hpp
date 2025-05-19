// wof_opcode_handlers.hpp
#pragma once

#include "wof_interpreter.hpp"
#include <iostream>

inline void registerCoreControlOps(WofInterpreter& vm) {
    // Function definition start (⊕)
    vm.registerOpcode(1, [](WofInterpreter& vm, const WofToken& t) {
        if (t.position + 1 >= vm.tokens.size()) {
            std::cerr << "[⊕] Missing symbol after function declaration\n";
            return;
        }

        const auto& next = vm.tokens[t.position + 1];
        std::string name(1, static_cast<char>(next.glyph));  // crude: assume ASCII symbol
        size_t bodyStart = t.position + 2;

        vm.defineFunction(name, bodyStart);
        std::cout << "[⊕] Defined function: " << name << " at position " << bodyStart << "\n";
    });

    // Block start ⺆ (no-op for now)
    vm.registerOpcode(6, [](WofInterpreter&, const WofToken&) {
        // could mark entry into block scope
    });

    // Block end ⺘ (return from function)
    vm.registerOpcode(7, [](WofInterpreter& vm, const WofToken&) {
        std::cout << "[ret] ⺘ returning from function\n";
        vm.instructionPointerOverride = std::nullopt;
    });

    // Call function (symbol assumed on stack)
    vm.registerOpcode(99, [](WofInterpreter& vm, const WofToken&) {
        int64_t symbolId = vm.pop();
        std::string name(1, static_cast<char>(symbolId));
        vm.callFunction(name);
    });
}
