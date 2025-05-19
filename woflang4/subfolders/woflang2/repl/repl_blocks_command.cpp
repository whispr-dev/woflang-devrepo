// repl_blocks_command.cpp
// Implements the :blocks REPL command to show nesting structure

#include "block_tracking_support.hpp"
#include <iostream>

void handle_blocks_command(const BlockRegistry& registry) {
    std::cout << "[BLOCKS]\n";
    for (const auto& b : registry.getBlocks()) {
        std::cout << " ⺆ IP " << b.startIP << " (" << b.type << ") → ⺘ IP " << b.endIP << "\n";
    }
}
