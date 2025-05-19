// list_block_tokenizer_nested.cpp
// Parses nested list blocks from [ ... ] into WofValue lists

#include "wof_value.hpp"
#include "wof_interpreter.hpp"
#include <iostream>

WofValue parseListBlock(const std::vector<WofToken>& tokens, size_t& ip, WofInterpreter& vm) {
    std::vector<WofValue> elements;
    ++ip; // skip '['

    while (ip < tokens.size()) {
        const auto& tok = tokens[ip];

        if (tok.glyph == U']') {
            break;  // End of list
        } else if (tok.glyph == U'[') {
            // Recursively parse inner list
            elements.push_back(parseListBlock(tokens, ip, vm));
        } else if (tok.opcode == 0 && tok.glyph >= U'0' && tok.glyph <= U'9') {
            elements.emplace_back(tok.glyph - U'0');
        } else {
            std::cerr << "[list] Unsupported token in list at IP " << ip << "\n";
        }

        ++ip;
    }

    return WofValue(elements);
}
