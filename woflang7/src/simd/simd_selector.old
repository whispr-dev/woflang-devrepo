// --- Tokenization/Parsing ---

std::vector<std::string> WoflangInterpreter::tokenize(const std::string& line) {
    // Simple split on whitespace and keep quoted strings
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void WoflangInterpreter::dispatch_token(const std::string& token) {
    // Try op first
    auto it = op_handlers.find(token);
    if (it != op_handlers.end()) {
        it->second(*this);
        return;
    }

    // Integer literal?
    try {
        size_t idx;
        int64_t val = std::stoll(token, &idx, 10);
        if (idx == token.size()) {
            stack.emplace_back(val);
            return;
        }
    } catch (...) {}

    // Double literal?
    try {
        size_t idx;
        double val = std::stod(token, &idx);
        if (idx == token.size()) {
            stack.emplace_back(val);
            return;
        }
    } catch (...) {}

    // Otherwise treat as string/symbol
    stack.emplace_back(token, WofType::Symbol);
}

void WoflangInterpreter::error(const std::string& msg) {
    std::cerr << msg << std::endl;
}
simd_utf32_parser.hpp
cpp#pragma once
#include <vector>
#include <string>
#include <cstdint>

#if defined(__AVX2__)
#include <immintrin.h> // AVX2
#endif

// Helper: convert UTF-8 string to UTF-32 (for woflang's glyph use)
inline std::u32string utf8_to_utf32(const std::string& input) {
    std::u32string out;
    size_t i = 0;
    while (i < input.size()) {
        char32_t ch = 0;
        unsigned char c = static_cast<unsigned char>(input[i]);
        if (c < 0x80) {
            ch = c;
            ++i;
        } else if ((c >> 5) == 0x6) {
            ch = ((c & 0x1F) << 6) | (static_cast<unsigned char>(input[i + 1]) & 0x3F);
            i += 2;
        } else if ((c >> 4) == 0xE) {
            ch = ((c & 0x0F) << 12) | ((static_cast<unsigned char>(input[i + 1]) & 0x3F) << 6) |
                 (static_cast<unsigned char>(input[i + 2]) & 0x3F);
            i += 3;
        } else if ((c >> 3) == 0x1E) {
            ch = ((c & 0x07) << 18) | ((static_cast<unsigned char>(input[i + 1]) & 0x3F) << 12) |
                 ((static_cast<unsigned char>(input[i + 2]) & 0x3F) << 6) |
                 (static_cast<unsigned char>(input[i + 3]) & 0x3F);
            i += 4;
        }
        out.push_back(ch);
    }
    return out;
}

// AVX2-based whitespace scanner (for ASCII/UTF-32 space/tab/newline)
inline std::vector<std::u32string> simd_utf32_tokenize(const std::u32string& line) {
    std::vector<std::u32string> tokens;
    
#if defined(__AVX2__)
    // AVX2 implementation
    size_t i = 0, start = 0, n = line.size();
    while (i + 8 <= n) {
        // Load 8 codepoints at a time (32-bit)
        __m256i v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&line[i]));
        
        // Whitespace mask (U+0020, U+0009, U+000A, U+000D)
        __m256i space = _mm256_set1_epi32(0x20);
        __m256i tab = _mm256_set1_epi32(0x09);
        __m256i nl = _mm256_set1_epi32(0x0A);
        __m256i cr = _mm256_set1_epi32(0x0D);
        
        // Create mask where 1 means whitespace, 0 means non-whitespace
        __m256i space_mask = _mm256_cmpeq_epi32(v, space);
        __m256i tab_mask = _mm256_cmpeq_epi32(v, tab);
        __m256i nl_mask = _mm256_cmpeq_epi32(v, nl);
        __m256i cr_mask = _mm256_cmpeq_epi32(v, cr);
        
        // Combine masks (whitespace = 1, non-whitespace = 0)
        __m256i ws_mask = _mm256_or_si256(
            _mm256_or_si256(space_mask, tab_mask),
            _mm256_or_si256(nl_mask, cr_mask)
        );
        
        // Convert to bitmask (1 bit per 32-bit element)
        uint32_t mask = _mm256_movemask_ps(_mm256_castsi256_ps(ws_mask));
        
        // Process the mask bit by bit
        for (int j = 0; j < 8; ++j) {
            bool is_ws = (mask >> j) & 1;
            if (start < i + j && is_ws) {
                // End of token
                tokens.emplace_back(line.substr(start, i + j - start));
                start = i + j + 1;
            } else if (start == i + j && is_ws) {
                // Skip whitespace
                start = i + j + 1;
            }
        }
        
        i += 8;
    }
    
    // Process remaining chars
    while (i < n) {
        if (std::iswspace(line[i])) {
            if (start < i) {
                tokens.emplace_back(line.substr(start, i - start));
            }
            start = i + 1;
        }
        ++i;
    }
    
    // Add last token if any
    if (start < n) {
        tokens.emplace_back(line.substr(start, n - start));
    }
#else
    // Scalar fallback implementation
    size_t i = 0, start = 0;
    while (i < line.size()) {
        // Skip whitespace
        while (i < line.size() && std::iswspace(line[i])) ++i;
        start = i;
        while (i < line.size() && !std::iswspace(line[i])) ++i;
        if (start < i)
            tokens.emplace_back(line.substr(start, i - start));
    }
#endif
    
    return tokens;
}
plugin_loader.cpp (Fixed)
cpp#include "../core/woflang.hpp"