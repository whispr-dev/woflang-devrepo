// simd_utf32_neon.hpp
#pragma once

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include <arm_neon.h>
#include <vector>
#include <unordered_map>
#include <cstdint>

// NEON tokenization for UTF-32 glyph streams
inline std::vector<uint32_t> matchUtf32GlyphsNEON(const char32_t* glyphStream, size_t length, const std::unordered_map<char32_t, uint16_t>& glyphMap) {
    std::vector<uint32_t> matchingIndices;

    constexpr size_t stride = 4; // NEON 128-bit = 4 x 32-bit glyphs

    for (size_t i = 0; i + stride <= length; i += stride) {
        uint32x4_t chunk = vld1q_u32(reinterpret_cast<const uint32_t*>(&glyphStream[i]));
        for (int j = 0; j < stride; ++j) {
            char32_t g = glyphStream[i + j];
            if (glyphMap.find(g) != glyphMap.end()) {
                matchingIndices.push_back(static_cast<uint32_t>(i + j));
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

#endif
