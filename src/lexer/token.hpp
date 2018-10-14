#pragma once
#include <string>

namespace lexer
{

enum token_type
{
  INTEGER,
  DOUBLE,
  SYMBOL,
  STRING_LITERAL,
  PUNCTUATION,
  INVALID
};

struct token
{
  std::string file;
  unsigned int line;
  unsigned int cursor;
  token_type type;
  std::string value;

  explicit token(const std::string &file,
                 unsigned int line,
                 unsigned int cursor,
                 token_type type = INVALID,
                 const std::string &initial_value = "")
      : file(file),
        line(line),
        cursor(cursor),
        type(type),
        value("")
  {
    value += initial_value;
  }
};

} // namespace lexer