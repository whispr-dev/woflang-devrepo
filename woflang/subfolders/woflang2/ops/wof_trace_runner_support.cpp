// wof_trace_runner_support.cpp
// Adds trace toggle + step-logging support for WOFLANG

#include "block_tracking_support.hpp"
#include "wof_interpreter.hpp"
#include <iostream>

bool traceEnabled = false;

void enable_trace() {
    traceEnabled = true;
    std::cout << "[trace] Enabled.\n";
}

void disable_trace() {
    traceEnabled = false;
    std::cout << "[trace] Disabled.\n";
}

void trace_step(const WofInterpreter& vm, size_t ip) {
    if (ip >= vm.tokens.size()) return;

    const auto& tok = vm.tokens[ip];
    std::cout << "[TRACE] IP " << ip << " | Glyph: ";
    std::cout << static_cast<char32_t>(tok.glyph);
    std::cout << " | Opcode: " << tok.opcode;
    std::cout << " | Stack: [";

    std::stack<int64_t> temp = vm.dataStack;
    std::vector<int64_t> reversed;
    while (!temp.empty()) {
        reversed.push_back(temp.top());
        temp.pop();
    }
    for (auto it = reversed.rbegin(); it != reversed.rend(); ++it) {
        std::cout << *it;
        if (it + 1 != reversed.rend()) std::cout << ", ";
    }
    std::cout << "]\n";
}
