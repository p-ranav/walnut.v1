#include <lexer.hpp>

namespace lexer
{

  bool lexer::valid_symbol(std::string& character)
  {
    for (auto& c : character)
    {
      if ((c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        (c == '_') ||
        ((unsigned char)c >= 0xC0) ||
        ((unsigned char)c >= 0x80)) {
        continue;
      }
      else {
        return false;
      }
    }
    return true;
  }

  void lexer::symbol(std::string& character)
  {
    token result(file, line, cursor, character);

    while (true)
    {
      character = peek();

      if (valid_symbol(character)) {
        character = next();
        cursor += 1;

        result.value += character;
        continue;
      }
      else {
        break;
      }

    }

    cursor += 1;
    print(result, "symbol");
    tokens.push_back(result);

  }
}