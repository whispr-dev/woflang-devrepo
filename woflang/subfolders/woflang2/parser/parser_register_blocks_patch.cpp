// parser_register_blocks_patch.cpp
// Modify parseWoflangSIMD to register ⺆ ... ⺘ block ranges into BlockRegistry

#include "block_tracking_support.hpp"
#include "wof_interpreter.hpp"

void registerBlocksFromTokens(const std::vector<WofToken>& tokens, BlockRegistry& registry) {
    std::vector<size_t> blockStack;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& tok = tokens[i];
        if (tok.opcode == 6) {  // ⺆ block start
            blockStack.push_back(i);
        } else if (tok.opcode == 7) {  // ⺘ block end
            if (!blockStack.empty()) {
                size_t start = blockStack.back();
                blockStack.pop_back();
                std::string type = "block";

                if (start > 0) {
                    const auto& prev = tokens[start - 1];
                    switch (prev.opcode) {
                        case 1: type = "func"; break;       // ⊕
                        case 2: type = "if"; break;         // 若
                        case 201: type = "loop"; break;     // ⟳
                        case 202: type = "repeat"; break;   // ⨯
                        case 203: type = "for"; break;      // ⍺
                    }
                }

                registry.registerBlock(start, i, type);
            } else {
                std::cerr << "[block parse] Warning: unmatched ⺘ at IP " << i << "\n";
            }
        }
    }

    if (!blockStack.empty()) {
        std::cerr << "[block parse] Warning: unmatched ⺆ at IP(s): ";
        for (auto ip : blockStack) std::cerr << ip << " ";
        std::cerr << "\n";
    }
}
