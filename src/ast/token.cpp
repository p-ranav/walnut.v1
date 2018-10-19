#include <token.hpp>

Token::String TokenString(TokenType type)
{
  switch (type)
  {
  case TokenType::DOT_OPERATOR:
    return ".";
  case TokenType::COMMA_OPERATOR:
    return ",";
  case TokenType::COLON_OPERATOR:
    return ":";
  case TokenType::SEMI_COLON_OPERATOR:
    return ";";
  case TokenType::ADDITION_OPERATOR:
    return "+";
  case TokenType::SUBTRACTION_OPERATOR:
    return "-";
  case TokenType::MULTIPLICATION_OPERATOR:
    return "*";
  case TokenType::DIVISION_OPERATOR:
    return "/";
  case TokenType::MODULUS_OPERATOR:
    return "%";
  case TokenType::EQUALITY_OPERATOR:
    return "==";
  case TokenType::INEQUALITY_OPERATOR:
    return "!=";
  case TokenType::GREATER_THAN_OPERATOR:
    return ">";
  case TokenType::GREATER_THAN_OR_EQUAL_OPERATOR:
    return ">=";
  case TokenType::LESSER_THAN_OPERATOR:
    return "<";
  case TokenType::LESSER_THAN_OR_EQUAL_OPERATOR:
    return "<=";
  case TokenType::LEFT_PARENTHESIS:
    return "(";
  case TokenType::LEFT_CURLY_BRACES:
    return "{";
  case TokenType::LEFT_SQUARE_BRACKETS:
    return "[";
  case TokenType::RIGHT_PARENTHESIS:
    return ")";
  case TokenType::RIGHT_CURLY_BRACES:
    return "}";
  case TokenType::RIGHT_SQUARE_BRACKETS:
    return "]";
  case TokenType::BITWISE_AND_OPERATOR:
    return "&";
  case TokenType::BITWISE_OR_OPERATOR:
    return "|";
  case TokenType::BITWISE_XOR_OPERATOR:
    return "^";
  case TokenType::BITWISE_ONES_COMPLEMENT_OPERATOR:
    return "~";
  case TokenType::BITWISE_LEFT_SHIFT_OPERATOR:
    return "<<";
  case TokenType::BITWISE_RIGHT_SHIFT_OPERATOR:
    return ">>";
  case TokenType::LOGICAL_AND_OPERATOR:
    return "&&";
  case TokenType::LOGICAL_OR_OPERATOR:
    return "||";
  case TokenType::LOGICAL_NOT_OPERATOR:
    return "!";
  case TokenType::KEYWORD_TRUE:
    return "true";
  case TokenType::KEYWORD_FALSE:
    return "false";
  case TokenType::KEYWORD_IF:
    return "if";
  case TokenType::KEYWORD_ELSE:
    return "else";
  case TokenType::KEYWORD_WHILE:
    return "while";
  case TokenType::KEYWORD_FOR:
    return "for";
  case TokenType::KEYWORD_FUNCTION:
    return "function";
  case TokenType::KEYWORD_RETURN:
    return "return";
  default:
    return "";
  }
}