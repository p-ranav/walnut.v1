#ifndef LEXER_TOKEN
#define LEXER_TOKEN

#define TOKEN_LIST                                          \
  TOKEN(WHITESPACE, "whitespace")                           \
  TOKEN(END_OF_LINE, "eol")                                 \
  TOKEN(END_OF_FILE, "eof")                                 \
  TOKEN(SYMBOL, "symbol")                                   \
  TOKEN(STRING_LITERAL, "string")                           \
  TOKEN(PUNCTUATION, "punctuation")                         \
  TOKEN(NUMBER, "number")                                   \
  /* Delimiters */                                          \
  TOKEN(DOT, "dot")                                         \
  TOKEN(COMMA, "comma")                                     \
  TOKEN(COLON, "colon")                                     \
  TOKEN(SEMI_COLON, "semi_colon")                           \
  TOKEN(EXCLAMATION, "exclamation")                         \
  TOKEN(QUESTION, "question")                               \
  /* Comparison Operators */                                \
  TOKEN(EQUAL, "equal")                                     \
  TOKEN(NOT_EQUAL, "not_equal")                             \
  TOKEN(GREATER, "greater")                                 \
  TOKEN(GREATER_EQUAL, "greater_than_or_equal")             \
  TOKEN(LESSER, "less_than")                                \
  TOKEN(LESSER_EQUAL, "less_than_or_equal")                 \
  /* Paranthesis, Braces and Brackets */                    \
  TOKEN(LEFT_PARANTHESIS, "left_paranthesis")               \
  TOKEN(LEFT_CURLY, "left_curly")                           \
  TOKEN(LEFT_BRACKETS, "left_brackets")                     \
  TOKEN(RIGHT_PARANTHESIS, "right_paranthesis")             \
  TOKEN(RIGHT_CURLY, "right_curly")                         \
  TOKEN(RIGHT_BRACKETS, "right_brackets")                   \
  /* Arithmetic Operators */                                \
  TOKEN(ADD, "add")                                         \
  TOKEN(SUBTRACT, "subtract")                               \
  TOKEN(MULTIPLY, "multiply")                               \
  TOKEN(DIVIDE, "divide")                                   \
  TOKEN(MODULUS, "modulus")                                 \
  /* Assignment Operators */                                \
  TOKEN(ASSIGN, "assign")                                   \
  TOKEN(ADD_ASSIGN, "add_assign")                           \
  TOKEN(SUBTRACT_ASSIGN, "subtract_assign")                 \
  TOKEN(MULTIPLY_ASSIGN, "multiply_assign")                 \
  TOKEN(DIVIDE_ASSIGN, "divide_assign")                     \
  TOKEN(MODULUS_ASSIGN, "modulus_assign")                   \
  /* Bitwise Operators */                                   \
  TOKEN(BITWISE_AND, "bitwise_and")                         \
  TOKEN(BITWISE_OR, "bitwise_or")                           \
  TOKEN(BITWISE_NOT, "bitwise_not")                         \
  TOKEN(BITWISE_XOR, "bitwise_xor")                         \
  TOKEN(BITWISE_ONES_COMPLEMENT, "bitwise_ones_complement") \
  TOKEN(BITWISE_LEFT_SHIFT, "bitwise_left_shift")           \
  TOKEN(BITWISE_RIGHT_SHIFT, "bitwise_right_shift")

typedef enum
{
#define TOKEN(label, string) TOKEN_##label,
  TOKEN_LIST
#undef TOKEN
      TOKEN_INVALID
} token;

struct token_t
{
  token type;
  char *value;
  const char *file_path;
  unsigned int line;
  unsigned int cursor;
};

#endif