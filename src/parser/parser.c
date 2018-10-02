#include <parser.h>

list_t * parse(list_t * tokens)
{
  /* declarations */
  list_t * statements = NULL;         /* This is the parser result */
  list_iterator_t * tokens_iterator;  /* iterator for lexer tokens */
  token * current_token;              /* current lexer token under examination */
  token * peek_token;                 /* the token after current_token */
  size_t current_token_index;         /* current index into lexer->tokens */

  /* initialize token iterator */
  tokens_iterator = list_iterator_new(tokens, LIST_HEAD);

  /* initialize current_token and peek_token */
  current_token = NULL;
  peek_token = NULL;
  current_token_index = 0;

  /* make sure current_token and peek_token are initialized */
  next_token(current_token, peek_token, tokens_iterator);
  next_token(current_token, peek_token, tokens_iterator);

  /* start parsing statements */
  while (current_token != NULL && *current_token != TOKEN_END_OF_FILE)
  {
    /* node * statement = parse_statement(..); */
  }

  return statements;
}

void next_token(token * current_token, token * peek_token, list_iterator_t * iterator)
{
  current_token = peek_token;
  peek_token = list_iterator_next(iterator);
}