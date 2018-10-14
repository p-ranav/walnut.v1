#include <lexer.hpp>
#include <iostream>
#include <string>

namespace lexer
{

void lexer::number(std::string &character)
{
  token result(file, line, cursor, INTEGER, character);

  while (true)
  {
    character = peek();
    if (character.size() == 1 &&
        (character[0] == '.' || isdigit(character[0])))
    {
      character = next();
      result.value += character;
      continue;
    }
    break;
  }

  if (result.value.find(".") != std::string::npos)
    result.type = DOUBLE;

  tokens.push_back(result);
}

} 