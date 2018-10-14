#include <lexer.hpp>

namespace lexer
{

bool lexer::valid_whitespace(std::string &character)
{
  return (
      character[0] == ' ' ||
      character[0] == 0x09 ||
      character[0] == 0x08 ||
      character[0] == 0x0D);
}

void lexer::whitespace(std::string &character)
{
  while (true)
  {
    character = peek();
    if (valid_whitespace(character))
      character = next();
    else
      return;
  }
}

} 