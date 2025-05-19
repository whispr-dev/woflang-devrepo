#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>

// Example: actual table would be codegen from your Unicode cheatsheet .csv
inline const std::unordered_map<char32_t, std::string> woflang_glyph_map = {
    { U'π', "pi" },
    { U'∑', "sum" },
    { U'∂', "partial" },
    { U'√', "sqrt" },
    // ...more
};

// Lookup by glyph (UTF-32 codepoint)
inline std::string lookup_woflang_op(char32_t glyph) {
    auto it = woflang_glyph_map.find(glyph);
    if (it != woflang_glyph_map.end()) return it->second;
    return std::string(1, static_cast<char>(glyph)); // fallback: raw glyph as string
}
