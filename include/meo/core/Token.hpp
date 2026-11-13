#pragma once

#include <string>

namespace Token {
  enum TokenType {
    // Single-character tokens
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, SEMICOLON,

    // Single or double character tokens
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
    SLASH, SLASH_SLASH,

    // Literals
    IDENTIFIER, STRING, NUMBER,

    // Keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    // EOF
    EOF_TOKEN
  };

  struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token(TokenType _type, const std::string& _lexeme, int _line) {
      type = _type;
      lexeme = _lexeme;
      line = _line;
    }
  };
}; // namespace Token