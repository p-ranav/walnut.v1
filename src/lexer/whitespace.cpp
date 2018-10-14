#include <lexer.hpp>

namespace lexer
{
  bool lexer::valid_whitespace(std::string& character)
  {
    return (
      starts_with(character, ' ') ||
      starts_with(character, 0x09) ||
      starts_with(character, 0x08) ||
      starts_with(character, 0x0D));
  }

  void lexer::whitespace(std::string& character)
  {
    while (true)
    {
      character = peek();
      if (valid_whitespace(character))
      {
        character = next();
        continue;
      }
      return;
    }
  }

}