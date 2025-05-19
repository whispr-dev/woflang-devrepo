#pragma once

#include <cstdint>
#include <array>
#include <string>
#include <vector>
#include <immintrin.h> // For SIMD intrinsics

namespace woflang {
namespace simd {

// Utility class for SIMD-accelerated UTF-32 string operations
class Utf32 {
public:
    using char_type = char32_t;
    using string_type = std::basic_string<char_type>;
    using view_type = std::basic_string_view<char_type>;

    // Convert UTF-8 string to UTF-32
    static string_type from_utf8(const std::string& utf8_str);
    
    // Convert UTF-32 string to UTF-8
    static std::string to_utf8(const string_type& utf32_str);
    
    // Fast substring search using SIMD instructions
    static size_t find(view_type haystack, view_type needle);
    
    // Character classification functions optimized with SIMD
    static bool is_whitespace(char_type c);
    static bool is_alpha(char_type c);
    static bool is_digit(char_type c);
    static bool is_alphanumeric(char_type c);
    static bool is_identifier_start(char_type c);
    static bool is_identifier_part(char_type c);
    
    // Batch character classification using SIMD
    static std::vector<bool> find_whitespace(view_type text);
    static std::vector<bool> find_alpha(view_type text);
    static std::vector<bool> find_digit(view_type text);
    
    // Batch text transformations
    static string_type to_lower(view_type text);
    static string_type to_upper(view_type text);
};

// Inline implementations for simple character classifications
inline bool Utf32::is_whitespace(char_type c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

inline bool Utf32::is_alpha(char_type c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline bool Utf32::is_digit(char_type c) {
    return c >= '0' && c <= '9';
}

inline bool Utf32::is_alphanumeric(char_type c) {
    return is_alpha(c) || is_digit(c);
}

inline bool Utf32::is_identifier_start(char_type c) {
    return is_alpha(c) || c == '_';
}

inline bool Utf32::is_identifier_part(char_type c) {
    return is_alphanumeric(c) || c == '_';
}

// Implementation of from_utf8 (simplified for now)
inline Utf32::string_type Utf32::from_utf8(const std::string& utf8_str) {
    string_type result;
    result.reserve(utf8_str.size()); // At most this many characters
    
    for (size_t i = 0; i < utf8_str.size(); ) {
        unsigned char c = utf8_str[i++];
        
        if (c < 0x80) {
            // ASCII character
            result.push_back(static_cast<char_type>(c));
        } else if (c < 0xE0) {
            // 2-byte sequence
            if (i >= utf8_str.size()) break;
            char_type ch = ((c & 0x1F) << 6) | (utf8_str[i++] & 0x3F);
            result.push_back(ch);
        } else if (c < 0xF0) {
            // 3-byte sequence
            if (i + 1 >= utf8_str.size()) break;
            char_type ch = ((c & 0x0F) << 12) | 
                          ((utf8_str[i++] & 0x3F) << 6) | 
                           (utf8_str[i++] & 0x3F);
            result.push_back(ch);
        } else {
            // 4-byte sequence
            if (i + 2 >= utf8_str.size()) break;
            char_type ch = ((c & 0x07) << 18) | 
                          ((utf8_str[i++] & 0x3F) << 12) | 
                          ((utf8_str[i++] & 0x3F) << 6) | 
                           (utf8_str[i++] & 0x3F);
            result.push_back(ch);
        }
    }
    
    return result;
}

// Implementation of to_utf8 (simplified for now)
inline std::string Utf32::to_utf8(const string_type& utf32_str) {
    std::string result;
    result.reserve(utf32_str.size() * 4); // Worst case: 4 bytes per character
    
    for (char_type c : utf32_str) {
        if (c < 0x80) {
            // ASCII
            result.push_back(static_cast<char>(c));
        } else if (c < 0x800) {
            // 2-byte sequence
            result.push_back(static_cast<char>(0xC0 | (c >> 6)));
            result.push_back(static_cast<char>(0x80 | (c & 0x3F)));
        } else if (c < 0x10000) {
            // 3-byte sequence
            result.push_back(static_cast<char>(0xE0 | (c >> 12)));
            result.push_back(static_cast<char>(0x80 | ((c >> 6) & 0x3F)));
            result.push_back(static_cast<char>(0x80 | (c & 0x3F)));
        } else {
            // 4-byte sequence
            result.push_back(static_cast<char>(0xF0 | (c >> 18)));
            result.push_back(static_cast<char>(0x80 | ((c >> 12) & 0x3F)));
            result.push_back(static_cast<char>(0x80 | ((c >> 6) & 0x3F)));
            result.push_back(static_cast<char>(0x80 | (c & 0x3F)));
        }
    }
    
    return result;
}

// Simple find implementation (can be optimized with SIMD later)
inline size_t Utf32::find(view_type haystack, view_type needle) {
    if (needle.empty()) return 0;
    if (haystack.size() < needle.size()) return string_type::npos;
    
    for (size_t i = 0; i <= haystack.size() - needle.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < needle.size(); ++j) {
            if (haystack[i + j] != needle[j]) {
                match = false;
                break;
            }
        }
        if (match) return i;
    }
    
    return string_type::npos;
}

// Batch implementations (simplified for now)
inline std::vector<bool> Utf32::find_whitespace(view_type text) {
    std::vector<bool> result(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
        result[i] = is_whitespace(text[i]);
    }
    return result;
}

inline std::vector<bool> Utf32::find_alpha(view_type text) {
    std::vector<bool> result(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
        result[i] = is_alpha(text[i]);
    }
    return result;
}

inline std::vector<bool> Utf32::find_digit(view_type text) {
    std::vector<bool> result(text.size());
    for (size_t i = 0; i < text.size(); ++i) {
        result[i] = is_digit(text[i]);
    }
    return result;
}

inline Utf32::string_type Utf32::to_lower(view_type text) {
    string_type result(text);
    for (auto& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
    return result;
}

inline Utf32::string_type Utf32::to_upper(view_type text) {
    string_type result(text);
    for (auto& c : result) {
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
    }
    return result;
}

} // namespace simd
} // namespace woflang