#include <lexer.hpp>
#include <iostream>

namespace lexer
{

void lexer::string_literal(std::string &character)
{
  token result(file, line, cursor, STRING_LITERAL);
  while (true)
  {
    character = peek();

    if (character[0] == '\\')
    {
      character = next();
      if (character[0] == '\"' || character[0] == '\\')
      {
        character = next();
        result.value += character;
        continue;
      }

      if (character[0] == 0x0A || character[0] == EOF)
      {
        throw std::runtime_error("unterminated string literal");
      }

      result.value += character;
      continue;
    }

    if (character[0] != '\"' && character[0] != EOF)
    {
      character = next();
      result.value += character;
      continue;
    }

    if (character[0] == 0x0A || character[0] == EOF)
    {
      throw std::runtime_error("unterminated string literal");
    }

    next();
    break;
  }
  tokens.push_back(result);
}

} // namespace lexer