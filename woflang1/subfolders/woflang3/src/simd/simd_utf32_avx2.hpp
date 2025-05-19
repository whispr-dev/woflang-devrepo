#pragma once
#include <immintrin.h>
#include <vector>
#include <string>

inline std::vector<char32_t> simd_utf32_avx2(const std::u32string& line) {
    // SIMD-accelerated, returns all non-whitespace glyphs as vector
    std::vector<char32_t> out;
    size_t i = 0, n = line.size();
    while (i + 8 <= n) {
        __m256i v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&line[i]));
        for (int j = 0; j < 8; ++j) {
            char32_t ch = reinterpret_cast<const char32_t*>(&v)[j];
            if (ch != U' ' && ch != U'\t' && ch != U'\n')
                out.push_back(ch);
        }
        i += 8;
    }
    while (i < n) {
        char32_t ch = line[i];
        if (ch != U' ' && ch != U'\t' && ch != U'\n')
            out.push_back(ch);
        ++i;
    }
    return out;
}
