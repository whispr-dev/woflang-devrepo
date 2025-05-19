
// simd_utf32_avx2.hpp
#pragma once

#include <immintrin.h>
#include <vector>
#include <unordered_map>
#include <cstdint>

// Fast AVX2 broadcasted matching for UTF-32 glyphs
inline std::vector<uint32_t> matchUtf32GlyphsAVX2(const char32_t* glyphStream, size_t length, const std::unordered_map<char32_t, uint16_t>& glyphMap) {
    std::vector<uint32_t> matchingIndices;
    constexpr size_t stride = 8;

    std::vector<char32_t> matchSet;
    matchSet.reserve(glyphMap.size());
    for (const auto& [glyph, _] : glyphMap) {
        matchSet.push_back(glyph);
    }

    for (size_t i = 0; i + stride <= length; i += stride) {
        __m256i chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&glyphStream[i]));

        for (char32_t g : matchSet) {
            __m256i target = _mm256_set1_epi32(static_cast<int32_t>(g));
            __m256i cmp = _mm256_cmpeq_epi32(chunk, target);
            int mask = _mm256_movemask_ps(_mm256_castsi256_ps(cmp));

            while (mask) {
                int offset = __builtin_ctz(mask);
                matchingIndices.push_back(static_cast<uint32_t>(i + offset));
                mask &= ~(1 << offset);
            }
        }
    }

    for (size_t i = length - (length % stride); i < length; ++i) {
        if (glyphMap.find(glyphStream[i]) != glyphMap.end()) {
            matchingIndices.push_back(static_cast<uint32_t>(i));
        }
    }

    return matchingIndices;
}
