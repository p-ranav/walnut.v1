#ifndef TEST_LEXER_VARIABLE_DECLARATION
#define TEST_LEXER_VARIABLE_DECLARATION

#include <lexer.h>
#include <macros.h>
#include <list.h>

TEST_CASE(lexer_integer_variable_declaration)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[6] = { TOKEN_VAR, TOKEN_SYMBOL, TOKEN_ASSIGN, TOKEN_INTEGER, TOKEN_SEMI_COLON, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "var taxi_cab = 1729;";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer correctly tokenizes \"var taxi_cab = 1729;\"");

  /* Tokenize the buffer of characters */
  tokens = lexer_tokenize(file_path, file_size, buffer);

  /* post-processing step in lexical analysis */
  lexer_post_process(tokens);

  while (i < arrlen(expected_tokens))
  {
    /* get pointer to token and print token type and value */
    struct token_t * token = ((struct token_t *)(list_at(tokens, i))->val);

    /* check result list of lexer tokens */
    TEST_CHECK(expected_tokens[i] == token->type);

    /* if we're here, all good so far */
    i = i + 1;
  }

  /* cleanup after test */
  lexer_destroy(tokens);

  RETURN_TEST_SUCCESS();
}

TEST_CASE(lexer_float_variable_declaration)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[6] = { TOKEN_VAR, TOKEN_SYMBOL, TOKEN_ASSIGN, TOKEN_FLOAT, TOKEN_SEMI_COLON, TOKEN_END_OF_FILE };
  const char * test_label;

  /* set single locale for all purposes */
  setlocale(LC_ALL, "");

  /* Initialization */
  file_path = __FILE__;
  buffer = "var π = 3.1415f;";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer correctly tokenizes \"var π = 3.1415f;\"");

  /* Tokenize the buffer of characters */
  tokens = lexer_tokenize(file_path, file_size, buffer);

  /* post-processing step in lexical analysis */
  lexer_post_process(tokens);

  while (i < arrlen(expected_tokens))
  {
    /* get pointer to token and print token type and value */
    struct token_t * token = ((struct token_t *)(list_at(tokens, i))->val);

    /* check result list of lexer tokens */
    TEST_CHECK(expected_tokens[i] == token->type);

    /* if we're here, all good so far */
    i = i + 1;
  }

  /* cleanup after test */
  lexer_destroy(tokens);

  RETURN_TEST_SUCCESS();
}

TEST_CASE(lexer_double_variable_declaration)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[6] = { TOKEN_VAR, TOKEN_SYMBOL, TOKEN_ASSIGN, TOKEN_DOUBLE, TOKEN_SEMI_COLON, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "var e = 2.71828;";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer correctly tokenizes \"var e = 2.71828;\"");

  /* Tokenize the buffer of characters */
  tokens = lexer_tokenize(file_path, file_size, buffer);

  /* post-processing step in lexical analysis */
  lexer_post_process(tokens);

  while (i < arrlen(expected_tokens))
  {
    /* get pointer to token and print token type and value */
    struct token_t * token = ((struct token_t *)(list_at(tokens, i))->val);

    /* check result list of lexer tokens */
    TEST_CHECK(expected_tokens[i] == token->type);

    /* if we're here, all good so far */
    i = i + 1;
  }

  /* cleanup after test */
  lexer_destroy(tokens);

  RETURN_TEST_SUCCESS();
}

TEST_CASE(lexer_bool_variable_declaration)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[6] = { TOKEN_VAR, TOKEN_SYMBOL, TOKEN_ASSIGN, TOKEN_TRUE, TOKEN_SEMI_COLON, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "var check_success = true;";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer correctly tokenizes \"var check_success = true;\"");

  /* Tokenize the buffer of characters */
  tokens = lexer_tokenize(file_path, file_size, buffer);

  /* post-processing step in lexical analysis */
  lexer_post_process(tokens);

  while (i < arrlen(expected_tokens))
  {
    /* get pointer to token and print token type and value */
    struct token_t * token = ((struct token_t *)(list_at(tokens, i))->val);

    /* check result list of lexer tokens */
    TEST_CHECK(expected_tokens[i] == token->type);

    /* if we're here, all good so far */
    i = i + 1;
  }

  /* cleanup after test */
  lexer_destroy(tokens);

  RETURN_TEST_SUCCESS();
}

#endif