#pragma once //single parse

#include <ostream>
#include <string_view>

enum class TokenType{
    Let, 
    Fn, 

    IntType,
    BoolType,
    VoidType,

    While,
    If,
    Else,
    Return,

    Identifier,
    IntLiteral,
    BoolLiteral,

    Equals,
    DoubleEquals,
    NotEqual,

    Plus,
    Minus,
    Star,
    Slash,

    Less,
    LessEqual,
    Greater,
    GreaterEqual,
    Not,

    Colon,
    SemiColon,
    Comma,

    OpenParen,
    CloseParen,
    OpenBrace,
    CloseBrace,

    EOF_Token,
    Unknown
};

struct Token{
    TokenType type;
    std::string_view lexeme;
    int line;
    int column;
};

[[nodiscard]] inline const char* tokenTypeToString(TokenType type) noexcept{
    switch(type){
        case TokenType::Let: return "LET";
        case TokenType::Fn: return "FN";

        case TokenType::IntType: return "INT_TYPE";
        case TokenType::BoolType: return "BOOL_TYPE";
        case TokenType::VoidType: return "VOID_TYPE";

        case TokenType::While: return "WHILE";
        case TokenType::If: return "IF";
        case TokenType::Else: return "ELSE";
        case TokenType::Return: return "RETURN";

        case TokenType::Identifier: return "IDENTIFIER";
        case TokenType::IntLiteral: return "INT_LITERAL";
        case TokenType::BoolLiteral: return "BOOL_LITERAL";

        case TokenType::Equals: return "EQUALS";
        case TokenType::DoubleEquals: return "DOUBLE_EQUALS";
        case TokenType::NotEqual: return "NOT_EQUAL";

        case TokenType::Plus: return "PLUS";
        case TokenType::Minus: return "MINUS";
        case TokenType::Star: return "STAR";
        case TokenType::Slash: return "SLASH";

        case TokenType::Less: return "LESS";
        case TokenType::LessEqual: return "LESS_EQUAL";
        case TokenType::Greater: return "GREATER";
        case TokenType::GreaterEqual: return "GREATER_EQUAL";
        case TokenType::Not: return "NOT";

        case TokenType::Colon: return "COLON";
        case TokenType::SemiColon: return "SEMICOLON";
        case TokenType::Comma: return "COMMA";

        case TokenType::OpenParen: return "OPEN_PAREN";
        case TokenType::CloseParen: return "CLOSE_PAREN";
        case TokenType::OpenBrace: return "OPEN_BRACE";
        case TokenType::CloseBrace: return "CLOSE_BRACE";

        case TokenType::EOF_Token: return "EOF";
        case TokenType::Unknown: return "UNKNOWN";


    }
    return "UNKNOWN";
}
inline std::ostream& operator<<(std::ostream& os, TokenType type) {
    return os << tokenTypeToString(type);
}