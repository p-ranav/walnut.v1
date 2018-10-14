#include <lexer.hpp>
#include <iostream>

namespace lexer
{

void lexer::punctuation(std::string &character)
{
  token result(file, line, cursor, PUNCTUATION);
  if (ispunct(character[0]))
  {
    result.value += character;
    tokens.push_back(result);
  }
}

} // namespace lexer