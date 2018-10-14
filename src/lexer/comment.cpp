#include <lexer.hpp>
#include <iostream>

namespace lexer
{

void lexer::comment()
{
  std::string character = next();

  if (character[0] == '/')
  {
    line_comment(character);
  }
  else if (character[0] == '*')
  {
    block_comment(character);
  }
  else
  {
    token result(file, line, cursor, DIVISION_OPERATOR);
    result.value += character;
    tokens.push_back(result);
  }
}

void lexer::line_comment(std::string &character)
{
  while (character[0] != 0x0A && index < buffer.size())
  {
    character = next();
  }
  line += 1;
  cursor = 0;
}

void lexer::block_comment(std::string &character)
{
  while (true)
  {
    character = next();
    if (character[0] == EOF)
      throw std::runtime_error("unterminated block comment");

    if (character[0] == 0x0A)
    {
      line += 1;
      cursor = 0;
      continue;
    }

    if (character[0] == '*')
    {
      character = peek();

      if (character[0] == EOF)
        throw std::runtime_error("unterminated block comment");

      if (character[0] == '/')
      {
        next();
        next();
        return;
      }
    }
  }
}

} 