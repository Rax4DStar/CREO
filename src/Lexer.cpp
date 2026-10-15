#include "Lexer.hpp"

#include <stdexcept>
#include <string>

// Character Traversal Funcs.
char Lexer::peek() const noexcept{
    return(_pos < _source.size()) ? _source[_pos] : '\0';
}

char Lexer::advance() noexcept{
    const char current = _source[_pos++];

    if (current == '\n'){
        ++_line;
        _column = 1;
    } else {
        ++_column;
    }
    return current;
}

bool Lexer::match(char expected) noexcept{
    if(peek()!= expected){
        return false;
    }
    advance();
    return true;
}

//Classifying characters.
bool Lexer::isWhitespace(char c) noexcept{
    return c==' '||c=='\t'||c=='\n'||c=='\r';
}

bool Lexer::isDigit(char c) noexcept{
    return c>='0'&& c<='9';
}

bool Lexer::isAlpha(char c) noexcept{
    return(c>='a' && c<='z') || (c>='A' && c<='Z') || c=='_';
}

bool Lexer::isAlphaNumeric(char c) noexcept{
    return isAlpha(c) || isDigit(c);
}

//Token Create.
Token Lexer::makeToken(
    TokenType type,
    std::size_t startPos,
    int startLine,
    int startColumn
) const noexcept{
    const std::size_t length = _pos - startPos;
    const std::string_view sourceView(_source);

    return Token{
        type,
        sourceView.substr(startPos, length),
        startLine,
        startColumn
    };
}

TokenType Lexer::classifyKeyword(std::string_view text) noexcept{
     if (text == "let")    return TokenType::Let;
     if (text == "fn")     return TokenType::Fn;
     
     if (text == "int")    return TokenType::IntType;
     if (text == "bool")   return TokenType::BoolType;
     if (text == "void")   return TokenType::VoidType;
     
     if (text == "while")  return TokenType::While;
     if (text == "if")     return TokenType::If;
     if (text == "else")   return TokenType::Else;
     if (text == "return") return TokenType::Return;
     
     if (text == "true")   return TokenType::BoolLiteral;
     if (text == "false")  return TokenType::BoolLiteral;

     return TokenType::Identifier;
}

//Tokenisation.
std::vector<Token> Lexer::tokenise(){
    std::vector<Token> tokens;
    tokens.reserve(_source.size()/4);

    while(peek()!='\0'){
        if(isWhitespace(peek())){
            advance();
            continue;
        }
        const std::size_t startPos = _pos;
        const int startLine = _line;
        const int startColumn = _column;
        const char current = advance();

        if(isDigit(current)){
            while(isDigit(peek())){
                advance();
            }
            tokens.push_back(makeToken(
                TokenType::IntLiteral,
                startPos,
                startLine,
                startColumn
            ));
            continue;
        }
        if(isAlpha(current)){
            while(isAlphaNumeric(peek())){
                advance();
            }

            const std::string_view text(_source.data() + startPos, _pos - startPos);

            tokens.push_back(makeToken(
                classifyKeyword(text),
                startPos,
                startLine,
                startColumn
            ));
            continue;
        }
        switch(current){
            case '=':
                tokens.push_back(makeToken(
                    match('=') ? TokenType::DoubleEquals:TokenType::Equals,
                    startPos,
                    startLine,
                    startColumn                   
                ));
                break;
            
            case '<':
                tokens.push_back(makeToken(
                    match('=') ? TokenType::LessEqual : TokenType::Less,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;
                
            case '!':
                tokens.push_back(makeToken(
                    match('=') ? TokenType::NotEqual : TokenType::Not,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;

            case '>':
                tokens.push_back(makeToken(
                    match('=') ? TokenType::GreaterEqual : TokenType::Greater,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;

            case '/':
                if (match('/')) {
                    while (peek() != '\n' && peek() != '\0') {
                        advance();
                    }
                } else {
                    tokens.push_back(makeToken(
                        TokenType::Slash,
                        startPos,
                        startLine,
                        startColumn
                    ));
                }
                break;

            case '+':
                tokens.push_back(makeToken(
                    TokenType::Plus,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;

            case '-':
                tokens.push_back(makeToken(
                    TokenType::Minus,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;

            case '*':
                tokens.push_back(makeToken(
                    TokenType::Star,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;

            case ':':
                tokens.push_back(makeToken(
                    TokenType::Colon,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;

            case ';':
                tokens.push_back(makeToken(
                    TokenType::SemiColon,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;

            case ',':
                tokens.push_back(makeToken(
                    TokenType::Comma,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;

            case '(':
                tokens.push_back(makeToken(
                    TokenType::OpenParen,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;

            case ')':
                tokens.push_back(makeToken(
                    TokenType::CloseParen,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;

            case '{':
                tokens.push_back(makeToken(
                    TokenType::OpenBrace,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;

            case '}':
                tokens.push_back(makeToken(
                    TokenType::CloseBrace,
                    startPos,
                    startLine,
                    startColumn
                ));
                break;

            default:
                throw std::runtime_error(
                    "Unexpected Character '"+ std::string(1, current) + "' at" + std::to_string(startLine) + ':' + std::to_string(startColumn)
                );
        }
    }
      tokens.push_back(Token{
        TokenType::EOF_Token,
        {},
        _line,
        _column
    });

    return tokens;
}
