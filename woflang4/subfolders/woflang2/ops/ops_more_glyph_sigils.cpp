// ops_more_glyph_sigils.cpp
// Implements more fun glyph sigils: 🎲, 🧿, ⟇

#pragma once
#include "wof_interpreter.hpp"
#include <iostream>
#include <random>

void register_more_glyph_sigils(WofInterpreter& vm) {
    // 🎲 push random glyph-as-int (chaotic glyph injection)
    vm.registerOpcode(4042, [](WofInterpreter& vm, const WofToken&) {
        static const std::vector<char32_t> chaosGlyphs = {
            U'∂', U'⨯', U'⊗', U'∫', U'⊕', U'π', U'ℯ',
            U'↻', U'🛑', U'☠', U'💀', U'🧿', U'⌁', U'∿'
        };
        std::random_device rd;
        std::mt19937 gen(rd());
        char32_t g = chaosGlyphs[gen() % chaosGlyphs.size()];
        vm.push(static_cast<int64_t>(g));
        std::cout << "[🎲] Chaos glyph pushed: " << static_cast<char32_t>(g) << std::endl;
    });

    // 🧿 divine protect — disables all opcode overrides
    vm.registerOpcode(4043, [](WofInterpreter& vm, const WofToken&) {
        std::cout << "[🧿] Glyph sanctum activated. No overrides will be accepted." << std::endl;
        vm.protectOps = true;
    });

    // ⟇ fold reality — push stack size, pop all, push stack size again
    vm.registerOpcode(4044, [](WofInterpreter& vm, const WofToken&) {
        size_t size = vm.valueStack.size();
        while (!vm.valueStack.empty()) vm.valueStack.pop();
        vm.push(static_cast<int64_t>(size));
        std::cout << "[⟇] Reality folded. Past stack replaced with its own length." << std::endl;
    });
}
