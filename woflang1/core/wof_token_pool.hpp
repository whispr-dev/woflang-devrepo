// wof_token_pool.hpp
#pragma once

#include <vector>
#include <stack>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include "parse_woflang_simd.cpp"

class WofTokenPool {
public:
    WofTokenPool(size_t capacity = 4096) {
        tokenStorage.reserve(capacity);
    }

    WofToken* alloc(char32_t glyph, uint16_t opcode, uint32_t pos) {
        if (!freeList.empty()) {
            WofToken* token = freeList.top();
            freeList.pop();
            *token = WofToken{glyph, opcode, pos};
            return token;
        }
        tokenStorage.emplace_back(WofToken{glyph, opcode, pos});
        return &tokenStorage.back();
    }

    void free(WofToken* token) {
        freeList.push(token);
    }

    void reset() {
        freeList = std::stack<WofToken*>();
        for (auto& token : tokenStorage) {
            freeList.push(&token);
        }
    }

    void clear() {
        tokenStorage.clear();
        freeList = std::stack<WofToken*>();
    }

private:
    std::vector<WofToken> tokenStorage;
    std::stack<WofToken*> freeList;
};
