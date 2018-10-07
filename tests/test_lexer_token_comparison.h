#ifndef TEST_LEXER_TOKEN_COMPARISON
#define TEST_LEXER_TOKEN_COMPARISON

#include <lexer.h>
#include <macros.h>
#include <list.h>

TEST_CASE(lexer_token_comparison_equal)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_EQUAL, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "==";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"==\" as {TOKEN_EQUAL, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_comparison_not_equal)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_NOT_EQUAL, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "!=";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"!=\" as {TOKEN_NOT_EQUAL, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_comparison_greater)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_GREATER, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = ">";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \">\" as {TOKEN_GREATER, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_comparison_greater_equal)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_GREATER_EQUAL, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = ">=";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \">=\" as {TOKEN_GREATER_EQUAL, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_comparison_lesser)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_LESSER, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "<";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"<\" as {TOKEN_LESSER, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_comparison_lesser_equal)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_LESSER_EQUAL, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "<=";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"<=\" as {TOKEN_LESSER_EQUAL, TOKEN_END_OF_FILE}");

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