#include <lexer.hpp>
#include <iostream>

namespace lexer
{
void lexer::punctuation(std::string &character)
{
  token result(file, line, cursor);

  if (ispunct(character[0]))
  {
    result.value += character;
    print(result, "punctuation");
    tokens.push_back(result);
  }
}
} // namespace lexer