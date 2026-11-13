#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#include <meo/core/Lexer.hpp>
#include <meo/core/Token.hpp>

// Helper functions for lexing
bool isAtEnd(const std::string& src, const int& current) {
  return current >= src.length();
}

char advance(const std::string& src, int& current) {
  return src[current++];
}

char peek(const std::string& src, const int& current) {
  return isAtEnd(src, current) ? '\0' : src[current];
}

char peekNext(const std::string& src, const int& current) {
  return isAtEnd(src, current + 1) ? '\0' : src[current + 1];
}

bool match(const std::string& src, int& current, char expected) {
  if (isAtEnd(src, current))
    return false;

  if (peek(src, current) != expected)
    return false;

  current++;
  return true;
}

std::vector<Token::Token> Lexer::lex(const std::string& src) {
  std::vector<Token::Token> tokens;
  
  int start = 0;
  int current = 0;
  int line = 1;

  // Lookup table for keywords
  static const std::unordered_map<std::string, Token::TokenType> keywords = {
    {"and"    , Token::AND},
    {"class"  , Token::CLASS},
    {"else"   , Token::ELSE},
    {"false"  , Token::FALSE},
    {"fun"    , Token::FUN},
    {"for"    , Token::FOR},
    {"if"     , Token::IF},
    {"nil"    , Token::NIL},
    {"or"     , Token::OR},
    {"print"  , Token::PRINT},
    {"return" , Token::RETURN},
    {"super"  , Token::SUPER},
    {"this"   , Token::THIS},
    {"true"   , Token::TRUE},
    {"var"    , Token::VAR},
    {"while"  , Token::WHILE}
  };

  while (!isAtEnd(src, current)) {
    start = current;
    char c = advance(src, current);

    switch (c) {
      // Single-character tokens
      case '(':
        tokens.emplace_back(Token::LEFT_PAREN, "(", line);
        break;
      case ')':
        tokens.emplace_back(Token::RIGHT_PAREN, ")", line);
        break;
      case '{':
        tokens.emplace_back(Token::LEFT_BRACE, "{", line);
        break;
      case '}':
        tokens.emplace_back(Token::RIGHT_BRACE, "}", line);
        break;
      case ',':
        tokens.emplace_back(Token::COMMA, ",", line);
        break;
      case '.':
        tokens.emplace_back(Token::DOT, ".", line);
        break;
      case ';':
        tokens.emplace_back(Token::SEMICOLON, ";", line);
        break;
      
      // Single or double character tokens need to be handled carefully
      case '!':
        if (match(src, current, '=')) {
          tokens.emplace_back(Token::BANG_EQUAL, "!=", line);
        } else {
          tokens.emplace_back(Token::BANG, "!", line);
        }
        break;
      case '=':
        if (match(src, current, '=')) {
          tokens.emplace_back(Token::EQUAL_EQUAL, "==", line);
        } else {
          tokens.emplace_back(Token::EQUAL, "=", line);
        }
        break;
      case '<':
        if (match(src, current, '=')) {
          tokens.emplace_back(Token::LESS_EQUAL, "<=", line);
        } else {
          tokens.emplace_back(Token::LESS, "<", line);
        }
        break;
      case '>':
        if (match(src, current, '=')) {
          tokens.emplace_back(Token::GREATER_EQUAL, ">=", line);
        } else {
          tokens.emplace_back(Token::GREATER, ">", line);
        }
        break;
      case '/':
        if (match(src, current, '/')) {
          // Handle single-line comments
          while (peek(src, current) != '\n' && !isAtEnd(src, current)) {
            advance(src, current);
          }
        } else {
          tokens.emplace_back(Token::SLASH, "/", line);
        }
        break;
      
      // Whitespace handling
      case ' ':
      case '\t':
      case '\r':
        break;
      
      // Newline handling
      case '\n':
        line++;
        break;

      // String literals
      case '"': 
        {
          std::ostringstream value;
          while (peek(src, current) != '"' && !isAtEnd(src, current)) {
            if (peek(src, current) == '\n')
              line++;

            value << advance(src, current);
          }

          if (isAtEnd(src, current)) {
            std::cerr << "Unterminated string at line " << line << std::endl;
            break;
          }

          advance(src, current); // Consume the closing "
          tokens.emplace_back(Token::STRING, value.str(), line);
        }
        break;
      
      // Number literals
      default:
        {
          if (std::isdigit(c)) {
            while (std::isdigit(peek(src, current))) {
              advance(src, current);
            }

            if (peek(src, current) == '.' && std::isdigit(peekNext(src, current))) {
              advance(src, current); // Consume the '.'

              while (std::isdigit(peek(src, current))) {
                advance(src, current);
              }
            }

            std::string numberStr = src.substr(start, current - start);
            tokens.emplace_back(Token::NUMBER, numberStr, line);
          } else if (std::isalpha(c) || c == '_') {
            while (std::isalnum(peek(src, current)) || peek(src, current) == '_') {
              advance(src, current);
            }

            std::string identifierStr = src.substr(start, current - start);

            // Check if the identifier is a keyword
            auto keywordIt = keywords.find(identifierStr);
            if (keywordIt != keywords.end()) {
              tokens.emplace_back(keywordIt->second, identifierStr, line);
            } else {
              tokens.emplace_back(Token::IDENTIFIER, identifierStr, line);
            }
          } else {
            std::cerr << "Unexpected character '" << c << "' at line " << line << std::endl;
          }
        }
    }
  }

  tokens.emplace_back(Token::EOF_TOKEN, "", line);

  return tokens;
}