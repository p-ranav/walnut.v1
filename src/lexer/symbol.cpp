#include <lexer.hpp>

namespace lexer
{

bool lexer::valid_symbol(std::string &character)
{
  for (auto &c : character)
  {
    if ((c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        (c == '_') ||
        ((unsigned char)c >= 0x80))
    {
      continue;
    }
    else
    {
      return false;
    }
  }
  return true;
}

void lexer::symbol(std::string &character)
{
  token result(file, line, cursor, SYMBOL, character);

  while (true)
  {
    character = peek();
    if (valid_symbol(character))
    {
      character = next();
      result.value += character;
      continue;
    }
    break;
  }
  tokens.push_back(result);
}

} // namespace lexer