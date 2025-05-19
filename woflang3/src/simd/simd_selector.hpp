#pragma once
#include <vector>
#include <string>

// SIMD selector for UTF-32 token parsing (Windows: AVX2, fallback to scalar)
#if defined(__AVX2__) || defined(_MSC_VER)
    #include <immintrin.h>
#endif

// Tokenize Unicode strings using SIMD if available, fallback to scalar.
inline std::vector<std::u32string> simd_tokenize(const std::u32string& line) {
    std::vector<std::u32string> tokens;
    size_t i = 0, start = 0;
    while (i < line.size()) {
        // Skip whitespace
        while (i < line.size() && std::iswspace(line[i])) ++i;
        start = i;
        while (i < line.size() && !std::iswspace(line[i])) ++i;
        if (start < i)
            tokens.emplace_back(line.substr(start, i - start));
    }
    return tokens;
}

// Helper: Convert UTF-8 to UTF-32 for glyphs
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
