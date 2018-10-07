#ifndef TEST_LEXER_TOKEN_BITWISE
#define TEST_LEXER_TOKEN_BITWISE

#include <lexer.h>
#include <macros.h>
#include <list.h>

TEST_CASE(lexer_token_bitwise_and)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_BITWISE_AND, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "&";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes \"&\" as {TOKEN_BITWISE_AND, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_bitwise_or)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_BITWISE_OR, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "|";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes \"|\" as {TOKEN_BITWISE_OR, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_bitwise_xor)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_BITWISE_XOR, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "^";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes \"^\" as {TOKEN_BITWISE_XOR, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_bitwise_ones_complement)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_BITWISE_ONES_COMPLEMENT, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "~";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes \"~\" as {TOKEN_BITWISE_ONES_COMPLEMENT, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_bitwise_left_shift)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_BITWISE_LEFT_SHIFT, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "<<";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes \"<<\" as {TOKEN_BITWISE_LEFT_SHIFT, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_bitwise_right_shift)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_BITWISE_RIGHT_SHIFT, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = ">>";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes \">>\" as {TOKEN_BITWISE_RIGHT_SHIFT, TOKEN_END_OF_FILE}");

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