// simd_avx2_module.hpp
#pragma once

#include <immintrin.h>
#include <vector>
#include <string>

inline std::vector<size_t> parseJsonSIMD_AVX2(const std::string& jsonStr) {
    const char* data = jsonStr.data();
    size_t len = jsonStr.size();
    std::vector<size_t> positions;

    __m256i openBrace = _mm256_set1_epi8('{');
    __m256i closeBrace = _mm256_set1_epi8('}');
    __m256i quote = _mm256_set1_epi8('"');

    for (size_t i = 0; i < len; i += 32) {
        __m256i chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(data + i));

        __m256i isOpen = _mm256_cmpeq_epi8(chunk, openBrace);
        __m256i isClose = _mm256_cmpeq_epi8(chunk, closeBrace);
        __m256i isQuote = _mm256_cmpeq_epi8(chunk, quote);

        uint32_t maskOpen = _mm256_movemask_epi8(isOpen);
        uint32_t maskClose = _mm256_movemask_epi8(isClose);
        uint32_t maskQuote = _mm256_movemask_epi8(isQuote);

        if (maskOpen) positions.push_back(i + __builtin_ctz(maskOpen));
        if (maskClose) positions.push_back(i + __builtin_ctz(maskClose));
        if (maskQuote) positions.push_back(i + __builtin_ctz(maskQuote));
    }

    return positions;
}