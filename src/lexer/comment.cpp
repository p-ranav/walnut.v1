#include <lexer.hpp>
#include <iostream>

namespace lexer 
{
  void lexer::comment()
  {
    std::string character = next();
    cursor += 2;

    if (starts_with(character, '/')) {
      line_comment(character);
    }
    else if (starts_with(character, '*')) {
      block_comment(character);
    }
    else {
      // TODO: save as TOKEN_DIVIDE
    }

  }

  void lexer::line_comment(std::string& character) {
    while (!starts_with(character, 0x0A) && index < buffer.size())
    {
      character = next();
      cursor += 1;
    }
    line += 1;
    cursor = 1;
  }

  void lexer::block_comment(std::string& character) {
    while (true)
    {
      character = next();
      cursor += 1;
      if (starts_with(character, EOF)) {
        std::cerr << "lexer error: block comment not terminated before end of file" << std::endl;
        abort();
      }

      if (starts_with(character, 0x0A)) {
        line += 1;
        cursor = 1;
        continue;
      }

      if (starts_with(character, '*')) {
        character = peek();

        if (starts_with(character, EOF)) {
          std::cerr << "lexer error: block comment not terminated before end of file" << std::endl;
          abort();
        }

        if (starts_with(character, '/')) {
          next();
          cursor += 1;
          next();
          cursor += 1;
          return;
        }
      }
    }
  }
}