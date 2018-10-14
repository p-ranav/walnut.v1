#include <lexer.hpp>
#include <iostream>

namespace lexer
{
  void lexer::string_literal(std::string& character)
  {
    token result(file, line, cursor);

    while (true)
    {
      character = peek();

      if (starts_with(character, '\\'))
      {
        character = next();
        if (starts_with(character, '\"') ||
          starts_with(character, '\\'))
        {
          character = next();
          result.value += character;
          continue;
        }

        if (starts_with(character, 0x0A) || 
          starts_with(character, EOF))
        {
          std::cerr << "lexer error: block comment not terminated before closing string literal" << std::endl;
          abort();
        }

        result.value += character;
        continue;
      }

      if (!starts_with(character, '\"') &&
        !starts_with(character, EOF)) {
        character = next();
        result.value += character;
        continue;
      }

      if (starts_with(character, 0x0A) || 
        starts_with(character, EOF))
      {
        std::cerr << "lexer error: block comment not terminated before closing string literal" << std::endl;
        abort();
      }

      next();
      break;
    }

    print(result, "string");
    tokens.push_back(result);
  }
}