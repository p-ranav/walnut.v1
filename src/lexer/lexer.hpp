#pragma once
#include <utf8.hpp>

#include <vector>
#include <stdlib.h>

namespace lexer
{
  class lexer {
  public:

    enum token {
      INVALID
    };

    struct lexer_context
    {
      std::string file;
      unsigned int line;
      unsigned int cursor;
    };
    lexer_context context;

    std::vector<token> tokenize(std::string file);

  private:

    std::string next(std::string& buffer, size_t& index);

    bool starts_with(const std::string& buffer, char character);

  };
}