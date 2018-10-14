#pragma once
#include <utf8.hpp>
#include <token.hpp>

#include <vector>
#include <stdlib.h>

namespace lexer
{
class lexer
{
public:
  std::vector<token> tokens;
  void tokenize(const std::string &file_path);

private:
  void print(token value, std::string type);

  std::string next(bool update_index = true);
  std::string peek();
  bool starts_with(const std::string &current, char character);

  void comment();
  void line_comment(std::string &character);
  void block_comment(std::string &character);

  void number(std::string &character);
  bool valid_symbol(std::string &character);
  void symbol(std::string &character);

  std::string file;
  unsigned int line;
  unsigned int cursor;
  std::string buffer;
  size_t index;
};
} // namespace lexer