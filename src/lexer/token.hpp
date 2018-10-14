#pragma once
#include <string>

namespace lexer
{
  enum token_type
  {
    INTEGER,
    DOUBLE,
    INVALID
  };

  struct token
  {
    std::string file;
    unsigned int line;
    unsigned int cursor;
    token_type type;
    std::string value;

    explicit token(std::string file, unsigned int line, unsigned int cursor, std::string initial_value = "") :
      file(file),
      line(line),
      cursor(cursor) {
      value = "";
      value += initial_value;
    }

  };

}