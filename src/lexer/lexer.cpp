#include <lexer.hpp>

#include <iostream>
#include <fstream>
#include <string>

namespace lexer
{

  std::vector<lexer::token> lexer::tokenize(std::string file_path)
  {
    std::vector<token> result;

    /* initialize context */
    file = file_path;
    line = 1;
    cursor = 1;

    /* read file into buffer */
    std::ifstream file_stream(file);
    buffer = std::string((std::istreambuf_iterator<char>(file_stream)),
      std::istreambuf_iterator<char>());

    for (index = 0; index < buffer.size();)
    {
      if (isutf(buffer[index]))
      {
        std::string current = next();
        std::cout << index << " " << current << std::endl;

        if (starts_with(current, '/'))
          tokenize_comment();

      }
    }

    return result;
  }

  std::string lexer::next()
  {
    std::string result = "";
    int length = u8_seqlen(&(buffer[index]));
    for (int i = 0; i < length; i++, index++)
    {
      result += buffer[index];
    }
    return result;
  }

  bool lexer::starts_with(const std::string& current, char character)
  {
    return (current[0] == character);
  }

  void lexer::tokenize_comment()
  {
    std::string character = next();
    cursor += 2;

    if (starts_with(character, '/')) {
      while (!starts_with(character, 0x0A) && index < buffer.size())
      {
        character = next();
        cursor += 1;
      }
      line += 1;
      cursor = 1;
    }

  }

}