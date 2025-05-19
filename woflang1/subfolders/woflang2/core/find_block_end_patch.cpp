// find_block_end_patch.cpp
// Adds findBlockEnd method to WofInterpreter

#include "wof_interpreter.hpp"

size_t WofInterpreter::findBlockEnd(size_t startIP) {
    int depth = 0;
    for (size_t i = startIP; i < tokens.size(); ++i) {
        const auto& tok = tokens[i];
        if (tok.opcode == 6) {      // ⺆ open block
            ++depth;
        } else if (tok.opcode == 7) { // ⺘ close block
            --depth;
            if (depth == 0) return i;
        }
    }
    std::cerr << "[error] No matching ⺘ found for block starting at IP " << startIP << "\n";
    return tokens.size();  // fallback: skip to end
}
