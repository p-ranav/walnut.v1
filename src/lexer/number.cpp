#include <lexer.hpp>
#include <iostream>
#include <string>

namespace lexer
{
void lexer::number(std::string &character)
{
  token result(file, line, cursor, character);

  while (true)
  {
    character = peek();
    if (character.size() == 1 &&
        (starts_with(character, '.') || isdigit(character[0])))
    {
      character = next();
      result.value += character;
      continue;
    }
    break;
  }

  if (result.value.find(".") != std::string::npos)
  {
    result.type = DOUBLE;
    print(result, "double");
  }
  else
  {
    result.type = INTEGER;
    print(result, "integer");
  }

  tokens.push_back(result);
}
} // namespace lexer