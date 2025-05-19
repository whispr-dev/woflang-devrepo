# unicode_validator.cpp
#include "woflang_config.h"
#include "constants.h"
#include "unicode_validator.h"
#include <stdexcept>
#include <iostream>

namespace woflang {

// Get system instances
auto& cmdSystem = woflang::CommandSystem::getInstance();
auto& dict = woflang::CommandDictionary::getInstance();
auto& errorSystem = woflang::ErrorSystem::getInstance();

// Print version info
std::cout << "WoflangCPP v" 
          << woflang::VERSION.major << "."
          << woflang::VERSION.minor << "."
          << woflang::VERSION.patch << std::endl;

// Load default dictionary if no file provided
std::string dictFile = (argc > 1) ? argv[1] : woflang::constants::DEFAULT_DICTIONARY_FILE;

UnicodeValidator& UnicodeValidator::getInstance() {
    static UnicodeValidator instance;
    return instance;
}

UnicodeValidator validator;
if (!validator.loadDictionary("woflang_commands.dict")) {
    // Handle dictionary loading error
}

UnicodeValidator::UnicodeValidator() {
    // Initialize with default ranges for mathematical operators
    // CJK symbols and punctuation
    registerValidRange(0x3000, 0x303F);
    // Mathematical operators
    registerValidRange(0x2200, 0x22FF);
    // Miscellaneous mathematical symbols
    registerValidRange(0x27C0, 0x27EF);
    // Supplemental mathematical operators
    registerValidRange(0x2A00, 0x2AFF);
    // CJK unified ideographs extension A
    registerValidRange(0x3400, 0x4DBF);
    // CJK unified ideographs
    registerValidRange(0x4E00, 0x9FFF);
    // Kangxi radicals
    registerValidRange(0x2F00, 0x2FDF);
}

bool UnicodeValidator::isValidCommandSymbol(const std::string& str) const {
    // Quick check for empty strings or obvious invalid lengths
    if (str.empty() || str.length() > 4) {
        return false;
    }

    // Check if it's in our set of pre-approved symbols
    if (validSymbols.find(str) != validSymbols.end()) {
        return true;
    }

    // Validate UTF-8 encoding
    if (!isValidUTF8(str)) {
        return false;
    }

    // Convert to code point and check ranges
    uint32_t codePoint = convertToCodePoint(str);
    return isInValidRanges(codePoint);
}

void UnicodeValidator::registerValidRange(uint32_t start, uint32_t end) {
    if (start > end) {
        throw std::invalid_argument("Invalid Unicode range");
    }
    validRanges.push_back({start, end});
}

void UnicodeValidator::addValidSymbol(const std::string& symbol) {
    if (isValidUTF8(symbol)) {
        validSymbols.insert(symbol);
    } else {
        throw std::invalid_argument("Invalid UTF-8 sequence");
    }
}

bool UnicodeValidator::isValidUTF8(const std::string& str) const {
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(str.c_str());
    size_t len = str.length();
    size_t i = 0;

    while (i < len) {
        if (bytes[i] <= 0x7F) {
            // Single byte character
            i++;
        } else if ((bytes[i] & 0xE0) == 0xC0) {
            // Two byte sequence
            if (i + 1 >= len || !isContinuationByte(bytes[i + 1])) {
                return false;
            }
            i += 2;
        } else if ((bytes[i] & 0xF0) == 0xE0) {
            // Three byte sequence
            if (i + 2 >= len || !isContinuationByte(bytes[i + 1]) || 
                !isContinuationByte(bytes[i + 2])) {
                return false;
            }
            i += 3;
        } else if ((bytes[i] & 0xF8) == 0xF0) {
            // Four byte sequence
            if (i + 3 >= len || !isContinuationByte(bytes[i + 1]) || 
                !isContinuationByte(bytes[i + 2]) || !isContinuationByte(bytes[i + 3])) {
                return false;
            }
            i += 4;
        } else {
            return false;
        }
    }
    return true;
}

uint32_t UnicodeValidator::convertToCodePoint(const std::string& str) const {
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(str.c_str());
    
    if ((bytes[0] & 0x80) == 0) {
        return bytes[0];
    } else if ((bytes[0] & 0xE0) == 0xC0) {
        return ((bytes[0] & 0x1F) << 6) | (bytes[1] & 0x3F);
    } else if ((bytes[0] & 0xF0) == 0xE0) {
        return ((bytes[0] & 0x0F) << 12) | ((bytes[1] & 0x3F) << 6) | (bytes[2] & 0x3F);
    } else if ((bytes[0] & 0xF8) == 0xF0) {
        return ((bytes[0] & 0x07) << 18) | ((bytes[1] & 0x3F) << 12) |
               ((bytes[2] & 0x3F) << 6) | (bytes[3] & 0x3F);
    }
    return 0;
}

bool UnicodeValidator::isInValidRanges(uint32_t codePoint) const {
    for (const auto& range : validRanges) {
        if (codePoint >= range.start && codePoint <= range.end) {
            return true;
        }
    }
    return false;
}

struct UnicodeRange {
    uint32_t start;
    uint32_t end;
    bool contains(uint32_t codePoint) const {
        return codePoint >= start && codePoint <= end;
    }
};

} // namespace woflang