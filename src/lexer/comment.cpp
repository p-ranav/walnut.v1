#include <lexer.hpp>
#include <iostream>

namespace lexer
{
void lexer::comment()
{
  std::string character = next();

  if (starts_with(character, '/'))
  {
    line_comment(character);
  }
  else if (starts_with(character, '*'))
  {
    block_comment(character);
  }
  else
  {
    // TODO: save as TOKEN_DIVIDE
  }
}

void lexer::line_comment(std::string &character)
{
  while (!starts_with(character, 0x0A) && index < buffer.size())
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
    if (starts_with(character, EOF))
    {
      std::cerr << "lexer error: block comment not terminated before end of file" << std::endl;
      abort();
    }

    if (starts_with(character, 0x0A))
    {
      line += 1;
      cursor = 0;
      continue;
    }

    if (starts_with(character, '*'))
    {
      character = peek();

      if (starts_with(character, EOF))
      {
        std::cerr << "lexer error: block comment not terminated before end of file" << std::endl;
        abort();
      }

      if (starts_with(character, '/'))
      {
        next();
        next();
        return;
      }
    }
  }
}
} // namespace lexer