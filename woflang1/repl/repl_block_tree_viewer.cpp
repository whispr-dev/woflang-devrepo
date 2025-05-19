// repl_block_tree_viewer.cpp
// Implements :tree REPL command to visualize nested blocks

#include "block_tracking_support.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

void handle_block_tree_command(const BlockRegistry& registry) {
    struct Node {
        const BlockInfo* block;
        std::vector<Node*> children;
    };

    std::vector<Node> nodes;
    std::map<size_t, Node*> startMap;

    // Create node for each block
    for (const auto& b : registry.getBlocks()) {
        nodes.push_back(Node{&b});
        startMap[b.startIP] = &nodes.back();
    }

    // Sort blocks by startIP
    std::sort(nodes.begin(), nodes.end(), [](const Node& a, const Node& b) {
        return a.block->startIP < b.block->startIP;
    });

    std::vector<Node*> rootNodes;

    for (auto& node : nodes) {
        bool foundParent = false;
        for (auto& parent : nodes) {
            if (node.block->startIP > parent.block->startIP &&
                node.block->endIP < parent.block->endIP) {
                parent.children.push_back(&node);
                foundParent = true;
                break;
            }
        }
        if (!foundParent) {
            rootNodes.push_back(&node);
        }
    }

    // Recursive tree print
    std::function<void(const Node*, int)> printTree = [&](const Node* node, int depth) {
        for (int i = 0; i < depth; ++i) std::cout << "  ";
        std::cout << "⺆ IP " << node->block->startIP << " (" << node->block->type << ") → ⺘ IP " << node->block->endIP << "\n";
        for (const auto* child : node->children) {
            printTree(child, depth + 1);
        }
    };

    std::cout << "[BLOCK TREE]\n";
    for (const auto* root : rootNodes) {
        printTree(root, 0);
    }
}
