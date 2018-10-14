#include <lexer.hpp>
#include <iostream>
#include <string>

namespace lexer 
{
  void lexer::number(std::string& character)
  {
    token result;
    result.file = file;
    result.line = line;
    result.cursor = cursor;
    result.value += character[0];

    while (true)
    {
      character = peek();
      if (character.size() == 1 &&
        (starts_with(character, '.') || isdigit(character[0])))
      {
        character = next();
        cursor += 1;
        result.value += character;
        continue;
      }
      break;
    }

    if (result.value.find(".") != std::string::npos) {
      result.type = DOUBLE;
      print(result, "double");
    }
    else {
      result.type = INTEGER;
      print(result, "integer");
    }

    tokens.push_back(result);
  }
}