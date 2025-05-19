#pragma once

namespace woflang {

// Enum for different token/symbol types in the language
enum class WofType {
    // Basic types
    Nil,
    Boolean,
    Number,
    String,
    
    // Symbols and operators
    Symbol,
    Operator,
    
    // Keywords
    Keyword,
    
    // Structural elements
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    LeftBracket,
    RightBracket,
    Comma,
    Semicolon,
    Colon,
    Dot,
    
    // Control flow
    If,
    Else,
    While,
    For,
    Return,
    
    // Functions and variables
    Function,
    Var,
    Const,
    Identifier,
    
    // End of file
    Eof,
    
    // Error token
    Error
};

// String representation of token types (for debugging)
inline const char* wof_type_to_string(WofType type) {
    switch (type) {
        case WofType::Nil: return "Nil";
        case WofType::Boolean: return "Boolean";
        case WofType::Number: return "Number";
        case WofType::String: return "String";
        case WofType::Symbol: return "Symbol";
        case WofType::Operator: return "Operator";
        case WofType::Keyword: return "Keyword";
        case WofType::LeftParen: return "LeftParen";
        case WofType::RightParen: return "RightParen";
        case WofType::LeftBrace: return "LeftBrace";
        case WofType::RightBrace: return "RightBrace";
        case WofType::LeftBracket: return "LeftBracket";
        case WofType::RightBracket: return "RightBracket";
        case WofType::Comma: return "Comma";
        case WofType::Semicolon: return "Semicolon";
        case WofType::Colon: return "Colon";
        case WofType::Dot: return "Dot";
        case WofType::If: return "If";
        case WofType::Else: return "Else";
        case WofType::While: return "While";
        case WofType::For: return "For";
        case WofType::Return: return "Return";
        case WofType::Function: return "Function";
        case WofType::Var: return "Var";
        case WofType::Const: return "Const";
        case WofType::Identifier: return "Identifier";
        case WofType::Eof: return "Eof";
        case WofType::Error: return "Error";
        default: return "Unknown";
    }
}

} // namespace woflang
