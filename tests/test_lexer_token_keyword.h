#ifndef TEST_LEXER_TOKEN_KEYWORD
#define TEST_LEXER_TOKEN_KEYWORD

#include <lexer.h>
#include <macros.h>
#include <list.h>

TEST_CASE(lexer_token_keyword_var)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_VAR, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "var";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"var\" as {TOKEN_VAR, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_if)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_IF, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "if";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"if\" as {TOKEN_IF, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_else)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_ELSE, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "else";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"else\" as {TOKEN_ELSE, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_else_if)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_ELSE_IF, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "else if";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"else if\" as {TOKEN_ELSE_IF, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_while)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_WHILE, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "while";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"while\" as {TOKEN_WHILE, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_for)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_FOR, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "for";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"for\" as {TOKEN_FOR, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_function)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_FUNCTION, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "function";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"function\" as {TOKEN_FUNCTION, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_lambda)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_FUNCTION, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "λ";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"λ\" as {TOKEN_FUNCTION, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_arrow)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_ARROW, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "->";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"->\" as {TOKEN_ARROW, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_return)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_RETURN, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "return";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"return\" as {TOKEN_RETURN, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_is)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_IS, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "is";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"is\" as {TOKEN_IS, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_in)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_IN, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "in";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"in\" as {TOKEN_IN, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_with)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_WITH, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "with";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"with\" as {TOKEN_WITH, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_try)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_TRY, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "try";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"try\" as {TOKEN_TRY, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_catch)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_CATCH, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "catch";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"catch\" as {TOKEN_CATCH, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_finally)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_FINALLY, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "finally";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"finally\" as {TOKEN_FINALLY, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_pass)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_PASS, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "pass";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"pass\" as {TOKEN_PASS, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_from)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_FROM, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "from";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"from\" as {TOKEN_FROM, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_import)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_IMPORT, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "import";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"import\" as {TOKEN_IMPORT, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_break)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_BREAK, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "break";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"break\" as {TOKEN_BREAK, TOKEN_END_OF_FILE}");

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

TEST_CASE(lexer_token_keyword_continue)
{
  /* Declarations */
  const char *file_path;
  list_t *tokens;
  char *buffer;
  size_t file_size;
  size_t i;
  token expected_tokens[2] = { TOKEN_CONTINUE, TOKEN_END_OF_FILE };
  const char * test_label;

  /* Initialization */
  file_path = __FILE__;
  buffer = "continue";
  file_size = strlen(buffer);
  i = 0;

  /* Log test name */
  DECLARE_TEST("Lexer tokenizes the input \"continue\" as {TOKEN_CONTINUE, TOKEN_END_OF_FILE}");

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