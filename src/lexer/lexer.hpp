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

    std::vector<token> tokenize(const std::string& file_path);

  private:

    std::string next(bool update_index = true);
    std::string peek();
    bool starts_with(const std::string& current, char character);

    void comment();
    void line_comment(std::string& character);
    void block_comment(std::string& character);

    void number() {}

    std::string file;
    unsigned int line;
    unsigned int cursor;
    std::string buffer;
    size_t index;
    std::vector<token> tokens;

  };
}