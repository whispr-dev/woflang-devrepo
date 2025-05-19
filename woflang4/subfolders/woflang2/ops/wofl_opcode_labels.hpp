// wof_opcode_labels.hpp
#pragma once

#include "wof_interpreter.hpp"
#include <iostream>

inline void registerLabelControlOps(WofInterpreter& vm) {
    // Define label — push string, then use "label" opcode (98)
    vm.registerOpcode(98, [](WofInterpreter& vm, const WofToken& t) {
        int64_t labelChar = vm.pop();
        std::string label(1, static_cast<char>(labelChar));
        vm.defineLabel(label, t.position + 1);
        std::cout << "[label] Defined: " << label << " at " << t.position + 1 << "\n";
    });

    // Jump to label — push string, then use "jump" opcode (97)
    vm.registerOpcode(97, [](WofInterpreter& vm, const WofToken&) {
        int64_t labelChar = vm.pop();
        std::string label(1, static_cast<char>(labelChar));
        vm.jumpToLabel(label);
    });
}