#pragma once
#include <string>

/* List of all lexer tokens
   When an input string is parsed by the lexer, our job is
   to look at this string of text and categorize it as one
   of the following tokens, e.g., "Hello" as STRING_LITERAL,
   3.14f as FLOAT, and ';' as SEMI_COLON.
*/
#define TOKEN_LIST                                               \
  TOKEN(WHITESPACE, "WHITESPACE", " ")                           \
  TOKEN(END_OF_LINE, "END_OF_LINE", "\n")                        \
  TOKEN(END_OF_FILE, "END_OF_FILE", "EOF")                       \
  TOKEN(SYMBOL, "SYMBOL", "symbol")                              \
  TOKEN(STRING_LITERAL, "STRING_LITERAL", "string")              \
  TOKEN(PUNCTUATION, "PUNCTUATION", "punctuation")               \
  TOKEN(NUMBER, "NUMBER", "number")                              \
  /* Delimiters */                                               \
  TOKEN(DOT, "DOT", ".")                                         \
  TOKEN(COMMA, "COMMA", ",")                                     \
  TOKEN(COLON, "COLON", ":")                                     \
  TOKEN(SEMI_COLON, "SEMI_COLON", ";")                           \
  TOKEN(EXCLAMATION, "EXCLAMATION", "!")                         \
  TOKEN(QUESTION, "QUESTION", "?")                               \
  /* Comparison Operators */                                     \
  TOKEN(EQUAL, "EQUAL", "==")                                    \
  TOKEN(NOT_EQUAL, "NOT_EQUAL", "!=")                            \
  TOKEN(GREATER, "GREATER", ">")                                 \
  TOKEN(GREATER_EQUAL, "GREATER_EQUAL", ">=")                    \
  TOKEN(LESSER, "LESSER", "<")                                   \
  TOKEN(LESSER_EQUAL, "LESSER_EQUAL", "<=")                      \
  /* Paranthesis, Braces and Brackets */                         \
  TOKEN(LEFT_PARANTHESIS, "LEFT_PARANTHESIS", "(")               \
  TOKEN(LEFT_CURLY, "LEFT_CURLY", "{")                           \
  TOKEN(LEFT_BRACKETS, "LEFT_BRACKETS", "[")                     \
  TOKEN(RIGHT_PARANTHESIS, "RIGHT_PARANTHESIS", ")")             \
  TOKEN(RIGHT_CURLY, "RIGHT_CURLY", "}")                         \
  TOKEN(RIGHT_BRACKETS, "RIGHT_BRACKETS", "]")                   \
  /* Arithmetic Operators */                                     \
  TOKEN(ADD, "ADD", "+")                                         \
  TOKEN(SUBTRACT, "SUBTRACT", "-")                               \
  TOKEN(MULTIPLY, "MULTIPLY", "*")                               \
  TOKEN(DIVIDE, "DIVIDE", "/")                                   \
  TOKEN(MODULUS, "MODULUS", "%")                                 \
  /* Assignment Operators */                                     \
  TOKEN(ASSIGN, "ASSIGN", "=")                                   \
  TOKEN(ADD_ASSIGN, "ADD_ASSIGN", "+=")                          \
  TOKEN(SUBTRACT_ASSIGN, "SUBTRACT_ASSIGN", "-=")                \
  TOKEN(MULTIPLY_ASSIGN, "MULTIPLY_ASSIGN", "*=")                \
  TOKEN(DIVIDE_ASSIGN, "DIVIDE_ASSIGN", "/=")                    \
  TOKEN(MODULUS_ASSIGN, "MODULUS_ASSIGN", "%=")                  \
  /* Bitwise Operators */                                        \
  TOKEN(BITWISE_AND, "BITWISE_AND", "&")                         \
  TOKEN(BITWISE_OR, "BITWISE_OR", "|")                           \
  TOKEN(BITWISE_XOR, "BITWISE_XOR", "^")                         \
  TOKEN(BITWISE_ONES_COMPLEMENT, "BITWISE_ONES_COMPLEMENT", "~") \
  TOKEN(BITWISE_LEFT_SHIFT, "BITWISE_LEFT_SHIFT", "<<")          \
  TOKEN(BITWISE_RIGHT_SHIFT, "BITWISE_RIGHT_SHIFT", ">>")        \
  /* Logical Operators */                                        \
  TOKEN(LOGICAL_AND, "LOGICAL_AND", "&&")                        \
  TOKEN(LOGICAL_OR, "LOGICAL_OR", "||")                          \
  /* Basic Data Types */                                         \
  TOKEN(INTEGER, "INTEGER", "int")                               \
  TOKEN(FLOAT, "FLOAT", "float")                                 \
  TOKEN(DOUBLE, "DOUBLE", "double")                              \
  /* Type inference */                                           \
  TOKEN(VAR, "VAR", "var")                                       \
  /* Keywords */                                                 \
  TOKEN(TRUE, "TRUE", "true")                                    \
  TOKEN(FALSE, "FALSE", "false")                                 \
  TOKEN(IF, "IF", "if")                                          \
  TOKEN(ELSE, "ELSE", "else")                                    \
  TOKEN(ELSE_IF, "ELSE_IF", "else if")                           \
  TOKEN(WHILE, "WHILE", "while")                                 \
  TOKEN(FOR, "FOR", "for")                                       \
  TOKEN(FUNCTION, "FUNCTION", "function")                        \
  TOKEN(ARROW, "ARROW", "->")                                    \
  TOKEN(RETURN, "RETURN", "return")                              \
  TOKEN(IS, "IS", "is")                                          \
  TOKEN(IN, "IN", "in")                                          \
  TOKEN(WITH, "WITH", "with")                                    \
  TOKEN(CONTINUE, "CONTINUE", "continue")                        \
  TOKEN(BREAK, "BREAK", "break")                                 \
  TOKEN(TRY, "TRY", "try")                                       \
  TOKEN(CATCH, "CATCH", "catch")                                 \
  TOKEN(FINALLY, "FINALLY", "finally")                           \
  TOKEN(PASS, "PASS", "pass")                                    \
  TOKEN(FROM, "FROM", "from")                                    \
  TOKEN(IMPORT, "IMPORT", "import")

/* Enum of tokens */
typedef enum
{
#define TOKEN(label, string, value) TOKEN_##label,
  TOKEN_LIST
#undef TOKEN
  TOKEN_INVALID
} token_type;

/* Each token stores
   (1) type (e.g., TOKEN_SEMICOLON),
   (2) value (e.g., 3.14 or "Hello")
   (3) file path
   (4) line number in file
   (5) cursor/character number in line
   */
struct token
{
  token_type type;
  std::string value;
  std::string file_path;
  unsigned int line;
  unsigned int cursor;
};