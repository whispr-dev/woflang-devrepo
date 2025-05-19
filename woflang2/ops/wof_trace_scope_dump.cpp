// wof_trace_scope_dump.cpp
// Adds scope variable inspection to trace_step_with_blocks()

#include "block_tracking_support.hpp"
#include "wof_interpreter.hpp"
#include <iostream>

extern bool traceEnabled;

void trace_step_with_scope(const WofInterpreter& vm, const BlockRegistry& registry, size_t ip) {
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
    std::cout << "]";

    std::cout << " | Scope: { ";
    if (!vm.scopeStack.empty()) {
        const auto& current = vm.scopeStack.top();
        for (auto it = current.begin(); it != current.end(); ++it) {
            std::cout << it->first << "=" << it->second;
            if (std::next(it) != current.end()) std::cout << ", ";
        }
    }
    std::cout << " }\n";
}
