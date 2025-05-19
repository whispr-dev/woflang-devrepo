#ifndef REPL_KEYBIND_EXPANSION_PATCH_HPP
#define REPL_KEYBIND_EXPANSION_PATCH_HPP

#include <string>
#include <string_view>

// Forward declarations for required classes
class KeyBindingManager;

// Function declarations
std::string expandKeybindings(const std::string& input, KeyBindingManager& keybinds);

// For Windows, use the Windows API functions
#ifdef _WIN32
#include <Windows.h>

inline std::string utf32_to_utf8(const std::u32string& utf32_str) {
    if (utf32_str.empty()) return std::string();
    
    // First convert UTF-32 to UTF-16 (wchar_t on Windows)
    std::wstring utf16_str;
    utf16_str.reserve(utf32_str.size());
    for (char32_t ch : utf32_str) {
        if (ch <= 0xFFFF) {
            utf16_str.push_back(static_cast<wchar_t>(ch));
        }
        else {
            // Handle surrogate pairs for characters outside the BMP
            ch -= 0x10000;
            utf16_str.push_back(static_cast<wchar_t>(0xD800 + (ch >> 10)));
            utf16_str.push_back(static_cast<wchar_t>(0xDC00 + (ch & 0x3FF)));
        }
    }
    
    // Then convert UTF-16 to UTF-8 using Windows API
    if (utf16_str.empty()) return std::string();
    
    // Get required buffer size
    int size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), 
                                   static_cast<int>(utf16_str.size()), 
                                   nullptr, 0, nullptr, nullptr);
    
    // Perform the conversion
    std::string utf8_str(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), 
                         static_cast<int>(utf16_str.size()), 
                         &utf8_str[0], size, nullptr, nullptr);
    
    return utf8_str;
}

inline std::u32string utf8_to_utf32(const std::string& utf8_str) {
    if (utf8_str.empty()) return std::u32string();
    
    // First convert UTF-8 to UTF-16 (wchar_t on Windows)
    int size = MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), 
                                   static_cast<int>(utf8_str.size()), 
                                   nullptr, 0);
    
    std::wstring utf16_str(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), 
                        static_cast<int>(utf8_str.size()), 
                        &utf16_str[0], size);
    
    // Then convert UTF-16 to UTF-32
    std::u32string utf32_str;
    utf32_str.reserve(utf16_str.size());
    
    for (size_t i = 0; i < utf16_str.size(); ++i) {
        char32_t ch = utf16_str[i];
        
        // Check for surrogate pairs
        if (ch >= 0xD800 && ch <= 0xDBFF && i + 1 < utf16_str.size()) {
            char32_t low_surrogate = utf16_str[i + 1];
            if (low_surrogate >= 0xDC00 && low_surrogate <= 0xDFFF) {
                // Combine the surrogate pair
                ch = 0x10000 + ((ch - 0xD800) << 10) + (low_surrogate - 0xDC00);
                ++i;  // Skip the low surrogate on the next iteration
            }
        }
        
        utf32_str.push_back(ch);
    }
    
    return utf32_str;
}

#endif // _WIN32

#endif // REPL_KEYBIND_EXPANSION_PATCH_HPP