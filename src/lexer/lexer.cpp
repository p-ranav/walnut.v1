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
      if (character[0] == '/')
        comment();
      else if (isdigit(character[0]))
        number(character);
      else if (valid_symbol(character))
        symbol(character);
      else if (valid_whitespace(character))
        whitespace(character);
      else if (character[0] == '"')
        string_literal(character);
      else if (ispunct(character[0]))
        punctuation(character);

      /* if newline is encountered, update line and reset cursor */
      if (character[0] == '\n')
      {
        line += 1;
        cursor = 0;
      }

      continue;
    }
  }

  /* update token type for 2-character operator sequences */
  for (size_t i = 0; i < tokens.size(); i++)
  {
    /* assignment operators */
    token_pair(i, ADDITION_OPERATOR, ASSIGNMENT_OPERATOR, ADD_AND_ASSIGN_OPERATOR, "+=");
    token_pair(i, SUBTRACTION_OPERATOR, ASSIGNMENT_OPERATOR, SUBTRACT_AND_ASSIGN_OPERATOR, "-=");
    token_pair(i, MULTIPLICATION_OPERATOR, ASSIGNMENT_OPERATOR, MULTIPLY_AND_ASSIGN_OPERATOR, "*=");
    token_pair(i, DIVISION_OPERATOR, ASSIGNMENT_OPERATOR, DIVIDE_AND_ASSIGN_OPERATOR, "/=");
    token_pair(i, MODULUS_OPERATOR, ASSIGNMENT_OPERATOR, MODULUS_AND_ASSIGN_OPERATOR, "%=");

    /* comparison operators */
    token_pair(i, ASSIGNMENT_OPERATOR, ASSIGNMENT_OPERATOR, EQUALITY_OPERATOR, "==");
    token_pair(i, LOGICAL_NOT_OPERATOR, ASSIGNMENT_OPERATOR, INEQUALITY_OPERATOR, "!=");
    token_pair(i, GREATER_THAN_OPERATOR, ASSIGNMENT_OPERATOR, GREATER_THAN_OR_EQUAL_OPERATOR, ">=");
    token_pair(i, LESSER_THAN_OPERATOR, ASSIGNMENT_OPERATOR, LESSER_THAN_OR_EQUAL_OPERATOR, "<=");

    /* bitwise operators */
    token_pair(i, LESSER_THAN_OPERATOR, LESSER_THAN_OPERATOR, BITWISE_LEFT_SHIFT_OPERATOR, "<<");
    token_pair(i, GREATER_THAN_OPERATOR, GREATER_THAN_OPERATOR, BITWISE_RIGHT_SHIFT_OPERATOR, ">>");

    /* logical operators */
    token_pair(i, BITWISE_AND_OPERATOR, BITWISE_AND_OPERATOR, LOGICAL_AND_OPERATOR, "&&");
    token_pair(i, BITWISE_OR_OPERATOR, BITWISE_OR_OPERATOR, BITWISE_OR_OPERATOR, "||");
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
    cursor += 1;
  }
  return result;
}

std::string lexer::peek()
{
  return next(false);
}

void lexer::token_pair(size_t &index, token_type first, token_type second, token_type result, const std::string &result_value)
{
  auto &current = tokens[index].type;
  auto next = (index + 1) < tokens.size() ? tokens[index + 1].type : INVALID;

  if (current == first && next == second)
  {
    current = result;
    tokens[index].value = result_value;
    tokens.erase(tokens.begin() + index + 1);
  }
}

} // namespace lexer