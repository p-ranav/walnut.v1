#include <lexer.hpp>

#include <iostream>
#include <fstream>
#include <string>

namespace lexer
{

  std::vector<lexer::token> lexer::tokenize(const std::string& file_path)
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
        std::string character = next();
        if (starts_with(character, '/'))
          comment();
        else if (isdigit(character[0]))
          number();
      }
    }

    return result;
  }

  std::string lexer::next(bool update_index)
  {
    std::string result = "";
    int length = u8_seqlen(&(buffer[index]));
    for (int i = 0; i < length; i++, index++)
    {
      result += buffer[index];
    }
    if (!update_index) {
      index -= length;
    }
    return result;
  }

  std::string lexer::peek() {
    return next(false);
  }

  bool lexer::starts_with(const std::string& current, char character)
  {
    return (current[0] == character);
  }

}