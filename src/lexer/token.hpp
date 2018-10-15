#pragma once
#include <string>
#include <vector>

struct Token
{
  enum Type
  {
    INTEGER,
    DOUBLE,
    SYMBOL,
    STRING_LITERAL,
    PUNCTUATION,

    // Delimiter Operators
    DOT_OPERATOR,
    COMMA_OPERATOR,
    COLON_OPERATOR,
    SEMI_COLON_OPERATOR,

    // Arithmetic Operators
    ADDITION_OPERATOR,
    SUBTRACTION_OPERATOR,
    MULTIPLICATION_OPERATOR,
    DIVISION_OPERATOR,
    MODULUS_OPERATOR,

    // Assignment Operators
    ASSIGNMENT_OPERATOR,
    ADD_AND_ASSIGN_OPERATOR,
    SUBTRACT_AND_ASSIGN_OPERATOR,
    MULTIPLY_AND_ASSIGN_OPERATOR,
    DIVIDE_AND_ASSIGN_OPERATOR,
    MODULUS_AND_ASSIGN_OPERATOR,

    // Comparison Operators
    EQUALITY_OPERATOR,
    INEQUALITY_OPERATOR,
    GREATER_THAN_OPERATOR,
    GREATER_THAN_OR_EQUAL_OPERATOR,
    LESSER_THAN_OPERATOR,
    LESSER_THAN_OR_EQUAL_OPERATOR,

    // Brackets, Braces & PARENTHESIS
    LEFT_PARENTHESIS,
    LEFT_CURLY_BRACES,
    LEFT_SQUARE_BRACKETS,
    RIGHT_PARENTHESIS,
    RIGHT_CURLY_BRACES,
    RIGHT_SQUARE_BRACKETS,

    // Bitwise Operators
    BITWISE_AND_OPERATOR,
    BITWISE_OR_OPERATOR,
    BITWISE_XOR_OPERATOR,
    BITWISE_ONES_COMPLEMENT_OPERATOR,
    BITWISE_LEFT_SHIFT_OPERATOR,
    BITWISE_RIGHT_SHIFT_OPERATOR,

    // Logical Operators
    LOGICAL_AND_OPERATOR,
    LOGICAL_OR_OPERATOR,
    LOGICAL_NOT_OPERATOR,

    // Keywords
    KEYWORD_VAR,
    KEYWORD_TRUE,
    KEYWORD_FALSE,
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_WHILE,
    KEYWORD_FOR,
    KEYWORD_FUNCTION,
    KEYWORD_RETURN,

    END_OF_FILE,
    INVALID
  };
  typedef std::string String;
  typedef unsigned int UnsignedInt;

  String file;
  UnsignedInt line;
  UnsignedInt cursor;
  Type type;
  String value;

  Token() : file(""), line(1), cursor(0), type(INVALID), value("") {}

  explicit Token(const String &file,
                 UnsignedInt line,
                 UnsignedInt cursor,
                 Type type = INVALID,
                 const String &initial_value = "")
      : file(file),
        line(line),
        cursor(cursor),
        type(type),
        value("")
  {
    value += initial_value;
  }

};

typedef Token::Type TokenType;
typedef std::vector<Token> TokenVector;
typedef const std::vector<Token> &TokenVectorConstRef;