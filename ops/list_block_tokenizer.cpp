// list_block_tokenizer.cpp
// Parses tokens between [ ... ] into a WofValue list

#include "wof_value.hpp"
#include "wof_interpreter.hpp"
#include <iostream>
#include <stack>

WofValue parseListBlock(const std::vector<WofToken>& tokens, size_t& ip, WofInterpreter& vm) {
    std::vector<WofValue> elements;
    ++ip; // skip '[' token

    while (ip < tokens.size()) {
        const auto& tok = tokens[ip];
        if (tok.glyph == U']') break; // end of list

        if (tok.opcode == 0 && tok.glyph >= U'0' && tok.glyph <= U'9') {
            elements.emplace_back(tok.glyph - U'0');
        } else {
            std::cerr << "[list] unsupported token in list at IP " << ip << "\n";
        }
        ++ip;
    }

    return WofValue(elements);
}
