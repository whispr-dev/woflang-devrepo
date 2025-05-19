// repl_block_lookup_command.cpp
// Implements :block <ip> to display block containing a given instruction pointer

#include "block_tracking_support.hpp"
#include <iostream>
#include <sstream>

void handle_block_lookup_command(const BlockRegistry& registry, const std::string& input) {
    std::istringstream iss(input);
    std::string cmd;
    size_t ip;
    iss >> cmd >> ip;

    auto match = registry.blockContaining(ip);
    if (match) {
        std::cout << "[BLOCK MATCH]\n";
        std::cout << "⺆ IP " << match->startIP << " (" << match->type << ") → ⺘ IP " << match->endIP << "\n";
    } else {
        std::cout << "[block] No block contains IP " << ip << "\n";
    }
}
