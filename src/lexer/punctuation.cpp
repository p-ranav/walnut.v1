#include <lexer.hpp>
#include <iostream>

namespace lexer
{

void lexer::punctuation(std::string &character)
{
  token result(file, line, cursor, PUNCTUATION);
  result.value += character;

  // delimiters
  if (result.value == ".")
    result.type = DOT_OPERATOR;
  else if (result.value == ",")
    result.type = COMMA_OPERATOR;
  else if (result.value == ":")
    result.type = COLON_OPERATOR;
  else if (result.value == ";")
    result.type = SEMI_COLON_OPERATOR;

  // comparison operators
  else if (result.value == ">")
    result.type = GREATER_THAN_OPERATOR;
  else if (result.value == "<")
    result.type = LESSER_THAN_OPERATOR;

  // arithmetic operators
  else if (result.value == "+")
    result.type = ADDITION_OPERATOR;
  else if (result.value == "-")
    result.type = SUBTRACTION_OPERATOR;
  else if (result.value == "*")
    result.type = MULTIPLICATION_OPERATOR;
  else if (result.value == "/")
    result.type = DIVISION_OPERATOR;
  else if (result.value == "%")
    result.type = MODULUS_OPERATOR;

  // assignment operators */
  else if (result.value == "=")
    result.type = ASSIGNMENT_OPERATOR;

  // brackets, braces and paranthesis
  else if (result.value == "(")
    result.type = LEFT_PARANTHESIS;
  else if (result.value == "{")
    result.type = LEFT_CURLY_BRACES;
  else if (result.value == "[")
    result.type = LEFT_SQUARE_BRACKETS;
  else if (result.value == ")")
    result.type = RIGHT_PARANTHESIS;
  else if (result.value == "}")
    result.type = RIGHT_CURLY_BRACES;
  else if (result.value == "]")
    result.type = RIGHT_SQUARE_BRACKETS;

  // bitwise operators
  else if (result.value == "&")
    result.type = BITWISE_AND_OPERATOR;
  else if (result.value == "|")
    result.type = BITWISE_OR_OPERATOR;
  else if (result.value == "^")
    result.type = BITWISE_XOR_OPERATOR;
  else if (result.value == "~")
    result.type = BITWISE_ONES_COMPLEMENT_OPERATOR;

  // logical operators
  else if (result.value == "!")
    result.type = LOGICAL_NOT_OPERATOR;

  // unicode operators
  else if (result.value == "＝")
    result.type = ASSIGNMENT_OPERATOR;
  else if (result.value == "≥")
    result.type = GREATER_THAN_OR_EQUAL_OPERATOR;
  else if (result.value == "≤")
    result.type = LESSER_THAN_OR_EQUAL_OPERATOR;
  else if (result.value == "≠")
    result.type = INEQUALITY_OPERATOR;
  else if (result.value == "⋅")
    result.type = MULTIPLICATION_OPERATOR;
  else if (result.value == "•")
    result.type = MULTIPLICATION_OPERATOR;
  else if (result.value == "×")
    result.type = MULTIPLICATION_OPERATOR;

  tokens.push_back(result);
}

} // namespace lexer