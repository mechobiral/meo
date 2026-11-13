#pragma once

#include <string>
#include <vector>

#include <meo/core/Token.hpp>

namespace Lexer {
  std::vector<Token::Token> lex(const std::string& src);
}; // namespace Lexer