#include <token.hpp>

namespace walnut
{

Token::String TokenString(Token::Type type)
{
  switch (type)
  {
  case Token::Type::DOT_OPERATOR:
    return ".";
  case Token::Type::COMMA_OPERATOR:
    return ",";
  case Token::Type::COLON_OPERATOR:
    return ":";
  case Token::Type::SEMI_COLON_OPERATOR:
    return ";";
  case Token::Type::ADDITION_OPERATOR:
    return "+";
  case Token::Type::SUBTRACTION_OPERATOR:
    return "-";
  case Token::Type::MULTIPLICATION_OPERATOR:
    return "*";
  case Token::Type::DIVISION_OPERATOR:
    return "/";
  case Token::Type::MODULUS_OPERATOR:
    return "%";
  case Token::Type::EQUALITY_OPERATOR:
    return "==";
  case Token::Type::INEQUALITY_OPERATOR:
    return "!=";
  case Token::Type::GREATER_THAN_OPERATOR:
    return ">";
  case Token::Type::GREATER_THAN_OR_EQUAL_OPERATOR:
    return ">=";
  case Token::Type::LESSER_THAN_OPERATOR:
    return "<";
  case Token::Type::LESSER_THAN_OR_EQUAL_OPERATOR:
    return "<=";
  case Token::Type::LEFT_PARENTHESIS:
    return "(";
  case Token::Type::LEFT_CURLY_BRACES:
    return "{";
  case Token::Type::LEFT_SQUARE_BRACKETS:
    return "[";
  case Token::Type::RIGHT_PARENTHESIS:
    return ")";
  case Token::Type::RIGHT_CURLY_BRACES:
    return "}";
  case Token::Type::RIGHT_SQUARE_BRACKETS:
    return "]";
  case Token::Type::BITWISE_AND_OPERATOR:
    return "&";
  case Token::Type::BITWISE_OR_OPERATOR:
    return "|";
  case Token::Type::BITWISE_XOR_OPERATOR:
    return "^";
  case Token::Type::BITWISE_ONES_COMPLEMENT_OPERATOR:
    return "~";
  case Token::Type::BITWISE_LEFT_SHIFT_OPERATOR:
    return "<<";
  case Token::Type::BITWISE_RIGHT_SHIFT_OPERATOR:
    return ">>";
  case Token::Type::LOGICAL_AND_OPERATOR:
    return "and";
  case Token::Type::LOGICAL_OR_OPERATOR:
    return "or";
  case Token::Type::LOGICAL_NOT_OPERATOR:
    return "!";
  case Token::Type::KEYWORD_TRUE:
    return "true";
  case Token::Type::KEYWORD_FALSE:
    return "false";
  case Token::Type::KEYWORD_IF:
    return "if";
  case Token::Type::KEYWORD_ELSE:
    return "else";
  case Token::Type::KEYWORD_WHILE:
    return "while";
  case Token::Type::KEYWORD_FOR:
    return "for";
  case Token::Type::KEYWORD_FUNCTION:
    return "function";
  case Token::Type::KEYWORD_RETURN:
    return "return";
  default:
    return "";
  }
}

} // namespace walnut