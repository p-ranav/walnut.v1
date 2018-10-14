#pragma once
#include <token.hpp>
#include <utf8.hpp>

#include <vector>
#include <stdlib.h>

namespace lexer
{
  class lexer {
  public:
    
    std::vector<token> tokenize(std::string file);

  private:

    std::string get_character(std::string& buffer, size_t& index);

    struct lexer_context
    {
      std::string file;
      unsigned int line;
      unsigned int cursor;
    };

    lexer_context context;

  };
}