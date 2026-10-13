#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "Token.hpp"

class Lexer{
    public:
        explicit Lexer(std::string source): _source(std::move(source)){}
        [[nodiscard]] std::vector<Token> tokenise();

    private:
        std::string _source;
        std::size_t _pos{0};

        int _line{1};
        int _column{1};

        [[nodiscard]] char peek() const noexcept;
        char advance() noexcept;
        bool match(char expected) noexcept;

        [[nodiscard]] static bool isWhitespace(char c) noexcept;
        [[nodiscard]] static bool isDigit(char c) noexcept;
        [[nodiscard]] static bool isAlpha(char c) noexcept;
        [[nodiscard]] static bool isAlphaNumeric(char c) noexcept;

        [[nodiscard]] Token makeToken(
            TokenType type,
            std::size_t startPos,
            int startLine,
            int startColumn
        ) const noexcept;
        
        [[nodiscard]] static TokenType classifyKeyword(
            std::string_view text
        ) noexcept;
};
    
