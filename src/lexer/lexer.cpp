#include <lexer.hpp>

#include <iostream>
#include <fstream>
#include <string>

namespace lexer
{

lexer::lexer() : file(""), line(1), cursor(0), buffer(""), index(0) {}

void lexer::tokenize(const std::string &file_path)
{
  /* read file into buffer */
  file = file_path;
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
        number(character);
      else if (valid_symbol(character))
        symbol(character);
      else if (valid_whitespace(character))
        whitespace(character);
      else if (starts_with(character, '"'))
        string_literal(character);
      else if (ispunct(character[0]))
        punctuation(character);

      /* if newline is encountered, update line and reset cursor */
      if (starts_with(character, '\n'))
      {
        line += 1;
        cursor = 0;
      }
    }
  }
}

std::string lexer::next(bool update_index)
{
  std::string result = "";
  int length = u8_seqlen(&(buffer[index]));
  for (int i = 0; i < length; i++, index++)
  {
    result += buffer[index];
  }
  if (!update_index)
  {
    index -= length;
  }
  else
  {
    cursor += length;
  }
  return result;
}

std::string lexer::peek()
{
  return next(false);
}

bool lexer::starts_with(const std::string &current, char character)
{
  return (current[0] == character);
}

void lexer::print(const token &token, const std::string &type)
{
  std::cout << "{ \"file\": \"" << token.file << "\""
            << ", \"line\": \"" << token.line << "\""
            << ", \"cursor\": \"" << token.cursor << "\""
            << ", \"type\": \"" << type << "\""
            << ", \"value\": \"" << token.value << "\""
            << std::endl;
}

} // namespace lexer