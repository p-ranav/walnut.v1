#pragma once
#include <token.hpp>
#include <utf8.hpp>

#include <vector>
#include <stdlib.h>

namespace lexer
{
  /*
    The lexer needs to do the following:
    (1) Take the sequence of bytes in the input buffer
    (2) correctly parsing unicode characters (UTF-8 encoding)
    (3) tokenize the stream of characters (build a list of tokens)
    (4) return the list of tokens
    Tokens can be of different categories (see token.hpp)
  */
  std::vector<token> tokenize(std::string file_path);
}