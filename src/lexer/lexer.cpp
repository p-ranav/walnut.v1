#include <lexer.hpp>

#include <iostream>
#include <fstream>
#include <string>

namespace lexer
{

  std::vector<lexer::token> lexer::tokenize(std::string file)
  {
    std::vector<token> result;

    /* initialize context */
    context.file = file;
    context.line = 1;
    context.cursor = 1;

    /* read file into buffer */
    std::ifstream file_stream(file);
    std::string buffer((std::istreambuf_iterator<char>(file_stream)),
      std::istreambuf_iterator<char>());

    for (size_t index = 0; index < buffer.size();)
    {
      if (isutf(buffer[index]))
      {
        std::string current = next(buffer, index);
        std::cout << index << " " << current << std::endl;

      }
    }

    return result;
  }

  std::string lexer::next(std::string& buffer, size_t& index)
  {
    std::string result = "";
    int length = u8_seqlen(&(buffer[index]));
    for (int i = 0; i < length; i++, index++)
    {
      result += buffer[index];
    }
    return result;
  }

  bool starts_with(const std::string& buffer, char character)
  {
    return (buffer[0] == character);
  }

}