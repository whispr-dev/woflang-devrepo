#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <immintrin.h> // AVX2

// Helper: convert UTF-8 string to UTF-32 (for woflang’s glyph use)
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

// AVX2-based whitespace scanner (for ASCII/UTF-32 space/tab/newline, extend for more Unicode spaces)
inline std::vector<std::u32string> simd_utf32_tokenize(const std::u32string& line) {
#if defined(__AVX2__)
    std::vector<std::u32string> tokens;
    size_t i = 0, start = 0, n = line.size();
    while (i + 8 <= n) {
        // Load 8 codepoints at a time (32-bit)
        __m256i v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&line[i]));
        // Whitespace mask (U+0020, U+0009, U+000A)
        __m256i space = _mm256_set1_epi32(0x20);
        __m256i tab
