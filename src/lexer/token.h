#ifndef LEXER_TOKEN
#define LEXER_TOKEN

#define TOKEN_LIST                                          \
  TOKEN(WHITESPACE, "WHITESPACE")                           \
  TOKEN(END_OF_LINE, "END_OF_LINE")                         \
  TOKEN(END_OF_FILE, "END_OF_FILE")                         \
  TOKEN(SYMBOL, "SYMBOL")                                   \
  TOKEN(STRING_LITERAL, "STRING_LITERAL")                   \
  TOKEN(PUNCTUATION, "PUNCTUATION")                         \
  TOKEN(NUMBER, "NUMBER")                                   \
  /* Delimiters */                                          \
  TOKEN(DOT, "DOT")                                         \
  TOKEN(COMMA, "COMMA")                                     \
  TOKEN(COLON, "COLON")                                     \
  TOKEN(SEMI_COLON, "SEMI_COLON")                           \
  TOKEN(EXCLAMATION, "EXCLAMATION")                         \
  TOKEN(QUESTION, "QUESTION")                               \
  /* Comparison Operators */                                \
  TOKEN(EQUAL, "EQUAL")                                     \
  TOKEN(NOT_EQUAL, "NOT_EQUAL")                             \
  TOKEN(GREATER, "GREATER")                                 \
  TOKEN(GREATER_EQUAL, "GREATER_EQUAL")                     \
  TOKEN(LESSER, "LESSER")                                   \
  TOKEN(LESSER_EQUAL, "LESSER_EQUAL")                       \
  /* Paranthesis, Braces and Brackets */                    \
  TOKEN(LEFT_PARANTHESIS, "LEFT_PARANTHESIS")               \
  TOKEN(LEFT_CURLY, "LEFT_CURLY")                           \
  TOKEN(LEFT_BRACKETS, "LEFT_BRACKETS")                     \
  TOKEN(RIGHT_PARANTHESIS, "RIGHT_PARANTHESIS")             \
  TOKEN(RIGHT_CURLY, "RIGHT_CURLY")                         \
  TOKEN(RIGHT_BRACKETS, "RIGHT_BRACKETS")                   \
  /* Arithmetic Operators */                                \
  TOKEN(ADD, "ADD")                                         \
  TOKEN(SUBTRACT, "SUBTRACT")                               \
  TOKEN(MULTIPLY, "MULTIPLY")                               \
  TOKEN(DIVIDE, "DIVIDE")                                   \
  TOKEN(MODULUS, "MODULUS")                                 \
  /* Assignment Operators */                                \
  TOKEN(ASSIGN, "ASSIGN")                                   \
  TOKEN(ADD_ASSIGN, "ADD_ASSIGN")                           \
  TOKEN(SUBTRACT_ASSIGN, "SUBTRACT_ASSIGN")                 \
  TOKEN(MULTIPLY_ASSIGN, "MULTIPLY_ASSIGN")                 \
  TOKEN(DIVIDE_ASSIGN, "DIVIDE_ASSIGN")                     \
  TOKEN(MODULUS_ASSIGN, "MODULUS_ASSIGN")                   \
  /* Bitwise Operators */                                   \
  TOKEN(BITWISE_AND, "BITWISE_AND")                         \
  TOKEN(BITWISE_OR, "BITWISE_OR")                           \
  TOKEN(BITWISE_NOT, "BITWISE_NOT")                         \
  TOKEN(BITWISE_XOR, "BITWISE_XOR")                         \
  TOKEN(BITWISE_ONES_COMPLEMENT, "BITWISE_ONES_COMPLEMENT") \
  TOKEN(BITWISE_LEFT_SHIFT, "BITWISE_LEFT_SHIFT")           \
  TOKEN(BITWISE_RIGHT_SHIFT, "BITWISE_RIGHT_SHIFT")         \
  /* Logical Operators */                                   \
  TOKEN(LOGICAL_AND, "LOGICAL_AND")                         \
  TOKEN(LOGICAL_OR, "LOGICAL_OR")                           \
  /* Basic Data Types */                                    \
  TOKEN(BYTE, "BYTE")                                       \
  TOKEN(UINT8, "UINT8")                                     \
  TOKEN(UINT16, "UINT16")                                   \
  TOKEN(UINT32, "UINT32")                                   \
  TOKEN(UINT64, "UINT64")                                   \
  TOKEN(INT8, "INT8")                                       \
  TOKEN(INT16, "INT16")                                     \
  TOKEN(INT32, "INT32")                                     \
  TOKEN(RUNE, "RUNE")                                       \
  TOKEN(INT64, "INT64")                                     \
  TOKEN(FLOAT32, "FLOAT32")                                 \
  TOKEN(FLOAT64, "FLOAT64")                                 \
  TOKEN(BOOL, "BOOL")                                       \
  TOKEN(STRING, "STRING")                                   \
  TOKEN(COMPLEX64, "COMPLEX64")                             \
  TOKEN(COMPLEX128, "COMPLEX128")                           \
  /* Type inference */                                      \
  TOKEN(LET, "LET")                                         \
  TOKEN(VAR, "VAR")                                         \
  /* Keywords */                                            \
  TOKEN(TRUE, "TRUE")                                       \
  TOKEN(FALSE, "FALSE")                                     \
  TOKEN(IF, "IF")                                           \
  TOKEN(ELSE, "ELSE")                                       \
  TOKEN(ELSE_IF, "ELSE_IF")                                 \
  TOKEN(WHILE, "WHILE")                                     \
  TOKEN(FOR, "FOR")                                         \
  TOKEN(FUNCTION, "FUNCTION")                               \
  TOKEN(RETURN, "RETURN")                                   \
  TOKEN(IS, "IS")                                           \
  TOKEN(IN, "IN")                                           \
  TOKEN(WITH, "WITH")                                       \
  TOKEN(CONTINUE, "CONTINUE")                               \
  TOKEN(BREAK, "BREAK")                                     \
  TOKEN(TRY, "TRY")                                         \
  TOKEN(CATCH, "CATCH")                                     \
  TOKEN(FINALLY, "FINALLY")                                 \
  TOKEN(PASS, "PASS")                                       \
  TOKEN(FROM, "FROM")                                       \
  TOKEN(IMPORT, "IMPORT")

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