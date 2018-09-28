#ifndef LEXER_TOKEN
#define LEXER_TOKEN

#define TOKEN_LIST                       \
  TOKEN(WHITESPACE, " ")                 \
  TOKEN(END_OF_LINE, "EOL")              \
  TOKEN(END_OF_FILE, "EOF")              \
  TOKEN(SYMBOL, "symbol")                \
  TOKEN(STRING_LITERAL, "string")        \
  TOKEN(PUNCTUATION, "punctuation")      \
  TOKEN(NUMBER, "number")                \
  /* Delimiters */                       \
  TOKEN(DOT, ".")                        \
  TOKEN(COMMA, ",")                      \
  TOKEN(COLON, ":")                      \
  TOKEN(SEMI_COLON, ";")                 \
  TOKEN(EXCLAMATION, "!")                \
  TOKEN(QUESTION, "?")                   \
  /* Comparison Operators */             \
  TOKEN(EQUAL, "==")                     \
  TOKEN(NOT_EQUAL, "!=")                 \
  TOKEN(GREATER, ">")                    \
  TOKEN(GREATER_EQUAL, ">=")             \
  TOKEN(LESSER, "<")                     \
  TOKEN(LESSER_EQUAL, "<=")              \
  /* Paranthesis, Braces and Brackets */ \
  TOKEN(LEFT_PARANTHESIS, "(")           \
  TOKEN(LEFT_CURLY, "{")                 \
  TOKEN(LEFT_BRACKETS, "[")              \
  TOKEN(RIGHT_PARANTHESIS, ")")          \
  TOKEN(RIGHT_CURLY, "}")                \
  TOKEN(RIGHT_BRACKETS, "]")             \
  /* Arithmetic Operators */             \
  TOKEN(ADD, "+")                        \
  TOKEN(SUBTRACT, "-")                   \
  TOKEN(MULTIPLY, "*")                   \
  TOKEN(DIVIDE, "/")                     \
  TOKEN(MODULUS, "%")                    \
  /* Assignment Operators */             \
  TOKEN(ASSIGN, "=")                     \
  TOKEN(ADD_ASSIGN, "+=")                \
  TOKEN(SUBTRACT_ASSIGN, "-=")           \
  TOKEN(MULTIPLY_ASSIGN, "*=")           \
  TOKEN(DIVIDE_ASSIGN, "/=")             \
  TOKEN(MODULUS_ASSIGN, "%=")            \
  /* Bitwise Operators */                \
  TOKEN(BITWISE_AND, "&")                \
  TOKEN(BITWISE_OR, "|")                 \
  TOKEN(BITWISE_NOT, "!")                \
  TOKEN(BITWISE_XOR, "^")                \
  TOKEN(BITWISE_ONES_COMPLEMENT, "~")    \
  TOKEN(BITWISE_LEFT_SHIFT, "<<")        \
  TOKEN(BITWISE_RIGHT_SHIFT, ">>")

typedef enum
{
#define TOKEN(label, string) TOKEN_##label,
  TOKEN_LIST
#undef TOKEN
  TOKEN_INVALID
} token;

static char *token_strings[] = {
#define TOKEN(label, string) string,
    TOKEN_LIST
#undef TOKEN
  "invalid"
};

struct token_t
{
  token type;
  char *value;
  const char *file_path;
  unsigned int line;
  unsigned int cursor;
};

#endif