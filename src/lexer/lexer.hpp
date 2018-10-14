#pragma once
#include <token.hpp>
#include <utf8.hpp>

#include <vector>
#include <stdlib.h>

namespace lexer
{
  struct lexer_context
  {
    std::string file;
    unsigned int line;
    unsigned int cursor;
  };

  std::vector<token> tokenize(std::string file);
  std::string get_character(std::string& buffer, size_t& index);
}