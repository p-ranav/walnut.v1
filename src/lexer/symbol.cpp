#include <lexer.hpp>

namespace lexer
{

bool lexer::valid_symbol(std::string &character)
{
  for (auto &c : character)
  {
    if ((c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        (c == '_') ||
        ((unsigned char)c >= 0x80))
      continue;
    else
      return false;
  }
  return true;
}

void lexer::symbol(std::string &character)
{
  token result(file, line, cursor, SYMBOL, character);

  while (true)
  {
    character = peek();
    if (valid_symbol(character))
    {
      character = next();
      result.value += character;
      continue;
    }
    break;
  }

  if (result.value == "var")
    result.type = KEYWORD_VAR;
  else if (result.value == "true")
    result.type = KEYWORD_TRUE;
  else if (result.value == "false")
    result.type = KEYWORD_FALSE;
  else if (result.value == "if")
    result.type = KEYWORD_IF;
  else if (result.value == "else")
    result.type = KEYWORD_ELSE;
  else if (result.value == "while")
    result.type = KEYWORD_WHILE;
  else if (result.value == "for")
    result.type = KEYWORD_FOR;
  else if (result.value == "function")
    result.type = KEYWORD_FUNCTION;
  else if (result.value == "ƒ")
    result.type = KEYWORD_FUNCTION;
  else if (result.value == "𝑓")
    result.type = KEYWORD_FUNCTION;
  else if (result.value == "return")
    result.type = KEYWORD_RETURN;

  tokens.push_back(result);
}

} // namespace lexer