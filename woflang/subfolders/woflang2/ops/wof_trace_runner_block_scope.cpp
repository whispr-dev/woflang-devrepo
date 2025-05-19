// wof_trace_runner_block_scope.cpp
// Enhances trace_step() to show block + scope context

#include "block_tracking_support.hpp"
#include "wof_interpreter.hpp"
#include <iostream>

extern bool traceEnabled;

void trace_step_with_blocks(const WofInterpreter& vm, const BlockRegistry& registry, size_t ip) {
    if (ip >= vm.tokens.size()) return;

    const auto& tok = vm.tokens[ip];
    std::cout << "[TRACE] IP " << ip << " | Glyph: ";
    std::cout << static_cast<char32_t>(tok.glyph);
    std::cout << " | Opcode: " << tok.opcode;

    if (auto block = registry.blockContaining(ip)) {
        std::cout << " | In Block: ⺆ IP " << block->startIP << " (" << block->type << ") → ⺘ IP " << block->endIP;
    }

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
