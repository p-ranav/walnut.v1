#ifndef TEST_LEXER_TOKEN_IDENTIFIER
#define TEST_LEXER_TOKEN_IDENTIFIER

#include <lexer.h>
#include <macros.h>
#include <list.h>
#include <utf8.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

TEST_CASE(lexer_token_identifier_ascii)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_SYMBOL, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "x";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"x\" as {TOKEN_SYMBOL, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_identifier_unicode_tamil)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_SYMBOL, TOKEN_END_OF_FILE };
  const char * test_label;

  /* set single locale for all purposes */
  setlocale(LC_ALL, "");

  /* Initialization */
  file_path = __FILE__;
  buffer = "வாழ்த்து";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"வாழ்த்து\" as {TOKEN_SYMBOL, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_identifier_unicode_smiley)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_SYMBOL, TOKEN_END_OF_FILE };
  const char * test_label;

  /* set single locale for all purposes */
  setlocale(LC_ALL, "");

  /* Initialization */
  file_path = __FILE__;
  buffer = "😀";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"😀\" as {TOKEN_SYMBOL, TOKEN_END_OF_FILE}");

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