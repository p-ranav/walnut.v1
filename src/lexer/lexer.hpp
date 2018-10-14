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

    std::string file;
    unsigned int line;
    unsigned int cursor;
    std::string buffer;
    size_t index;

    std::vector<token> tokenize(std::string file);

  private:

    std::string next(bool update_index = true);
    std::string peek();
    bool starts_with(const std::string& current, char character);

    void tokenize_comment();

  };
}