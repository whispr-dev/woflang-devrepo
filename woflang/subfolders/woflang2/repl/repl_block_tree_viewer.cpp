#include "block_tracking_support.hpp"
#include <iostream>
#include <functional>
#include <string>

void handle_block_tree_command(BlockRegistry& registry) {
    // Recursive function to print block tree
    std::function<void(const BlockInfo&, int)> printTree = [&](const BlockInfo& node, int depth) {
        // Indent based on depth
        std::cout << std::string(depth * 2, ' ') << "Block ID: " << node.id
                  << ", Type: " << node.type << ", IP: [" << node.startIP << "-" << node.endIP << "]\n";

        // Find child blocks
        for (const auto& child : registry.getBlocks()) {
            if (child.startIP > node.startIP && child.endIP < node.endIP) {
                printTree(child, depth + 1);
            }
        }
    };

    // Print top-level blocks
    for (const auto& block : registry.getBlocks()) {
        bool isTopLevel = true;
        for (const auto& other : registry.getBlocks()) {
            if (block.startIP > other.startIP && block.endIP < other.endIP) {
                isTopLevel = false;
                break;
            }
        }
        if (isTopLevel) {
            printTree(block, 0);
        }
    }
}