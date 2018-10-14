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
          consume_comment();

        std::cout << index << " " << buffer[index] << std::endl;

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

  void lexer::consume_comment()
  {
    std::string character = next();
    cursor += 2;

    if (starts_with(character, '/')) {
      consume_line_comment(character);
    }
    else if (starts_with(character, '*')) {
      consume_block_comment(character);
    }
    else {
      // TODO: save as TOKEN_DIVIDE
    }

  }

  void lexer::consume_line_comment(std::string& character) {
    while (!starts_with(character, 0x0A) && index < buffer.size())
    {
      character = next();
      cursor += 1;
    }
    line += 1;
    cursor = 1;
  }

  void lexer::consume_block_comment(std::string& character) {
    while (true)
    {
      character = next();
      cursor += 1;
      if (starts_with(character, EOF)) {
        std::cerr << "lexer error: block comment not terminated before end of file" << std::endl;
        abort();
      }

      if (starts_with(character, 0x0A)) {
        line += 1;
        cursor = 1;
        continue;
      }

      if (starts_with(character, '*')) {
        character = peek();

        if (starts_with(character, EOF)) {
          std::cerr << "lexer error: block comment not terminated before end of file" << std::endl;
          abort();
        }

        if (starts_with(character, '/')) {
          next();
          cursor += 1;
          next();
          cursor += 1;
          return;
        }
      }
    }
  }

}