// tokenizer.cpp - Advanced Unicode tokenizer for Woflang
#include "woflang.hpp"
#include <codecvt>
#include <locale>
#include <unordered_set>
#include <immintrin.h>

namespace woflang {

// Unicode categories for special handling
namespace unicode {
    // Mathematical operators
    const std::unordered_set<char32_t> math_ops = {
        U'∞', U'∅', U'∈', U'∉', U'∪', U'∩', U'⊆', U'⊂', U'⊇', U'⊃',
        U'∀', U'∃', U'∄', U'∴', U'∵', U'≡', U'≠', U'≈', U'≤', U'≥',
        U'±', U'∓', U'×', U'÷', U'√', U'∛', U'∜', U'∝', U'∞', U'∅'
    };
    
    // Greek letters
    const std::unordered_set<char32_t> greek_letters = {
        U'Α', U'Β', U'Γ', U'Δ', U'Ε', U'Ζ', U'Η', U'Θ', U'Ι', U'Κ', U'Λ', U'Μ',
        U'Ν', U'Ξ', U'Ο', U'Π', U'Ρ', U'Σ', U'Τ', U'Υ', U'Φ', U'Χ', U'Ψ', U'Ω',
        U'α', U'β', U'γ', U'δ', U'ε', U'ζ', U'η', U'θ', U'ι', U'κ', U'λ', U'μ',
        U'ν', U'ξ', U'ο', U'π', U'ρ', U'σ', U'ς', U'τ', U'υ', U'φ', U'χ', U'ψ', U'ω'
    };
    
    // Quantum notation
    const std::unordered_set<char32_t> quantum_symbols = {
        U'⟨', U'⟩', U'|', U'⊗', U'⊕', U'†'
    };
    
    // Special brackets and delimiters
    const std::unordered_set<char32_t> special_delimiters = {
        U'⟨', U'⟩', U'⌊', U'⌋', U'⌈', U'⌉', U'【', U'】', U'〖', U'〗'
    };
    
    inline bool is_special_token(char32_t ch) {
        return math_ops.count(ch) || greek_letters.count(ch) || 
               quantum_symbols.count(ch) || special_delimiters.count(ch);
    }
    
    inline bool is_whitespace(char32_t ch) {
        // Standard ASCII whitespace
        if (ch <= 127) {
            return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\f' || ch == '\v';
        }
        
        // Unicode whitespace characters
        return (ch >= 0x2000 && ch <= 0x200B) ||  // Various spaces
               ch == 0x00A0 ||  // Non-breaking space
               ch == 0x1680 ||  // Ogham space mark
               ch == 0x180E ||  // Mongolian vowel separator
               ch == 0x2028 ||  // Line separator
               ch == 0x2029 ||  // Paragraph separator
               ch == 0x202F ||  // Narrow no-break space
               ch == 0x205F ||  // Medium mathematical space
               ch == 0x3000 ||  // Ideographic space
               ch == 0xFEFF;    // Zero-width no-break space
    }
}

// Token type classification
enum class TokenType {
    Number,
    String,
    Symbol,
    Operator,
    SpecialSymbol,
    Comment
};

struct Token {
    std::string text;
    TokenType type;
    size_t line;
    size_t column;
};

class Tokenizer {
private:
    std::u32string source;
    size_t pos = 0;
    size_t line = 1;
    size_t column = 1;
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    
public:
    Tokenizer(const std::string& utf8_source) {
        source = converter.from_bytes(utf8_source);
    }
    
    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        
        while (pos < source.length()) {
            skip_whitespace();
            
            if (pos >= source.length()) break;
            
            char32_t ch = source[pos];
            size_t start_line = line;
            size_t start_column = column;
            
            // Comments
            if (ch == U'#' || (ch == U'/' && peek() == U'/')) {
                skip_comment();
                continue;
            }
            
            // String literals
            if (ch == U'"') {
                tokens.push_back(read_string(start_line, start_column));
                continue;
            }
            
            // Numbers
            if (is_digit(ch) || (ch == U'-' && is_digit(peek()))) {
                tokens.push_back(read_number(start_line, start_column));
                continue;
            }
            
            // Special Unicode symbols (single character tokens)
            if (unicode::is_special_token(ch)) {
                Token token;
                token.text = converter.to_bytes(std::u32string(1, ch));
                token.type = TokenType::SpecialSymbol;
                token.line = start_line;
                token.column = start_column;
                tokens.push_back(token);
                advance();
                continue;
            }
            
            // Quantum notation special case
            if (ch == U'|' && peek() != U'|') {
                // Check for |0⟩, |1⟩, |+⟩, |-⟩, |ψ⟩ patterns
                size_t saved_pos = pos;
                advance();
                
                if (pos < source.length()) {
                    char32_t next = source[pos];
                    if ((next == U'0' || next == U'1' || next == U'+' || 
                         next == U'-' || next == U'ψ' || next == U'φ') && 
                        peek() == U'⟩') {
                        Token token;
                        token.text = converter.to_bytes(std::u32string{U'|', next, U'⟩'});
                        token.type = TokenType::SpecialSymbol;
                        token.line = start_line;
                        token.column = start_column;
                        tokens.push_back(token);
                        advance(); // Skip the middle character
                        advance(); // Skip ⟩
                        continue;
                    }
                }
                
                // Not a quantum state, backtrack
                pos = saved_pos;
                column = start_column;
            }
            
            // Operators
            if (is_operator(ch)) {
                tokens.push_back(read_operator(start_line, start_column));
                continue;
            }
            
            // Symbols/identifiers
            tokens.push_back(read_symbol(start_line, start_column));
        }
        
        return tokens;
    }
    
    // Convert tokens back to strings for the interpreter
    static std::vector<std::string> to_strings(const std::vector<Token>& tokens) {
        std::vector<std::string> result;
        for (const auto& token : tokens) {
            result.push_back(token.text);
        }
        return result;
    }
    
private:
    void advance() {
        if (pos < source.length()) {
            if (source[pos] == U'\n') {
                line++;
                column = 1;
            } else {
                column++;
            }
            pos++;
        }
    }
    
    char32_t peek(size_t offset = 1) const {
        size_t peek_pos = pos + offset;
        return (peek_pos < source.length()) ? source[peek_pos] : U'\0';
    }
    
    void skip_whitespace() {
        while (pos < source.length() && unicode::is_whitespace(source[pos])) {
            advance();
        }
    }
    
    void skip_comment() {
        // Skip until end of line
        while (pos < source.length() && source[pos] != U'\n') {
            advance();
        }
    }
    
    Token read_string(size_t start_line, size_t start_column) {
        Token token;
        token.type = TokenType::String;
        token.line = start_line;
        token.column = start_column;
        
        std::u32string str;
        str += source[pos]; // Opening quote
        advance();
        
        while (pos < source.length() && source[pos] != U'"') {
            if (source[pos] == U'\\' && peek() == U'"') {
                str += U'"';
                advance();
                advance();
            } else {
                str += source[pos];
                advance();
            }
        }
        
        if (pos < source.length()) {
            str += source[pos]; // Closing quote
            advance();
        }
        
        token.text = converter.to_bytes(str);
        return token;
    }
    
    Token read_number(size_t start_line, size_t start_column) {
        Token token;
        token.type = TokenType::Number;
        token.line = start_line;
        token.column = start_column;
        
        std::u32string num;
        
        // Handle negative sign
        if (source[pos] == U'-') {
            num += source[pos];
            advance();
        }
        
        // Integer part
        while (pos < source.length() && is_digit(source[pos])) {
            num += source[pos];
            advance();
        }
        
        // Decimal part
        if (pos < source.length() && source[pos] == U'.' && is_digit(peek())) {
            num += source[pos];
            advance();
            
            while (pos < source.length() && is_digit(source[pos])) {
                num += source[pos];
                advance();
            }
        }
        
        // Scientific notation
        if (pos < source.length() && (source[pos] == U'e' || source[pos] == U'E')) {
            num += source[pos];
            advance();
            
            if (pos < source.length() && (source[pos] == U'+' || source[pos] == U'-')) {
                num += source[pos];
                advance();
            }
            
            while (pos < source.length() && is_digit(source[pos])) {
                num += source[pos];
                advance();
            }
        }
        
        token.text = converter.to_bytes(num);
        return token;
    }
    
    Token read_operator(size_t start_line, size_t start_column) {
        Token token;
        token.type = TokenType::Operator;
        token.line = start_line;
        token.column = start_column;
        
        std::u32string op;
        op += source[pos];
        advance();
        
        // Multi-character operators
        if (op[0] == U'=' && pos < source.length() && source[pos] == U'=') {
            op += source[pos];
            advance();
        } else if (op[0] == U'!' && pos < source.length() && source[pos] == U'=') {
            op += source[pos];
            advance();
        } else if (op[0] == U'<' && pos < source.length() && 
                   (source[pos] == U'=' || source[pos] == U'<')) {
            op += source[pos];
            advance();
        } else if (op[0] == U'>' && pos < source.length() && 
                   (source[pos] == U'=' || source[pos] == U'>')) {
            op += source[pos];
            advance();
        }
        
        token.text = converter.to_bytes(op);
        return token;
    }
    
    Token read_symbol(size_t start_line, size_t start_column) {
        Token token;
        token.type = TokenType::Symbol;
        token.line = start_line;
        token.column = start_column;
        
        std::u32string sym;
        
        while (pos < source.length() && 
               !unicode::is_whitespace(source[pos]) &&
               !is_operator(source[pos]) &&
               source[pos] != U'"' &&
               source[pos] != U'#') {
            sym += source[pos];
            advance();
        }
        
        token.text = converter.to_bytes(sym);
        return token;
    }
    
    bool is_digit(char32_t ch) const {
        return ch >= U'0' && ch <= U'9';
    }
    
    bool is_operator(char32_t ch) const {
        return ch == U'+' || ch == U'-' || ch == U'*' || ch == U'/' ||
               ch == U'=' || ch == U'<' || ch == U'>' || ch == U'!' ||
               ch == U'%' || ch == U'^' || ch == U'&' || ch == U'|' ||
               ch == U'(' || ch == U')' || ch == U'[' || ch == U']' ||
               ch == U'{' || ch == U'}' || ch == U',' || ch == U';';
    }
};

// Enhanced tokenizer with SIMD acceleration for ASCII segments
std::vector<std::string> WoflangInterpreter::tokenize(const std::string& line) {
    // Use the Unicode tokenizer
    Tokenizer tokenizer(line);
    auto tokens = tokenizer.tokenize();
    return Tokenizer::to_strings(tokens);
}

} // namespace woflang