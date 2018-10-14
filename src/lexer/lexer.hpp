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
    
    std::vector<token> tokenize(std::string file);

    struct lexer_context
    {
      std::string file;
      unsigned int line;
      unsigned int cursor;
    };

  private:

    std::string get_character(std::string& buffer, size_t& index);

    lexer_context context;

  };
}