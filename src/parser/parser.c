#include <parser.h>

list_t * parse(list_t * tokens)
{
  struct parser_t * parser = allocate(struct parser_t, 1);
  parser->statements = NULL;

  /* initialize token iterator */
  parser->tokens_iterator = list_iterator_new(tokens, LIST_HEAD);

  /* initialize current_token and peek_token */
  parser->current_token = NULL;
  parser->peek_token = NULL;
  parser->current_token_index = 0;

  /* make sure current_token and peek_token are initialized */
  next_token(parser);
  next_token(parser);

  /* start parsing statements */
  while (parser->current_token != NULL && *parser->current_token != TOKEN_END_OF_FILE)
  {
    /* node * statement = parse_statement(..); */
  }

  return parser->statements;
}

void next_token(struct parser_t * parser)
{
  parser->current_token = parser->peek_token;
  parser->peek_token = list_iterator_next(parser->tokens_iterator);
}

node * parse_statement(struct parser_t * parser)
{
  switch (*parser->current_token)
  {
  case TOKEN_VAR: 
    return parse_variable_declaration(parser);
    break;
  default:
    return NULL;
    break;
  }
}