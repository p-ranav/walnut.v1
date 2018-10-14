#include <lexer.hpp>

#include <iostream>
#include <fstream>
#include <string>

namespace lexer
{

  std::vector<token> tokenize(std::string file)
  {
    std::vector<token> result;

    /* read file into buffer */
    std::ifstream file_stream(file);
    std::string buffer((std::istreambuf_iterator<char>(file_stream)),
      std::istreambuf_iterator<char>());

    size_t index = 0;
    while (index < buffer.size())
    {
      if (isutf(buffer[index]))
      {
        /* get next character (potentially multi-byte) */
        std::string current = get_character(buffer, index);

      }
    }

    return result;
  }

  std::string get_character(std::string& buffer, size_t& index)
  {
    std::string result;

    int sequence_length = u8_seqlen(&(buffer[index]));

    int sequence_index = 0;
    while (sequence_index < sequence_length)
    {
      result += buffer[index];
      index += 1;
      sequence_index += 1;
    }

    return result;
  }

}