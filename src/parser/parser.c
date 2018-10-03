#include <parser.h>
#include <identifier_node.h>
#include <var_node.h>
#include <return_node.h>

extern const char *const token_strings[]; /* used in expect_peek */
extern node_interface *VAR_AS_NODE;
extern node_interface *RETURN_AS_NODE;

list_t * parse(list_t * tokens)
{
  struct parser_t * parser = allocate(struct parser_t, 1);
  parser->statements = list_new();

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
  while (!peek_token_is(parser, TOKEN_END_OF_FILE))
  {
    node * statement = parse_statement(parser);
    if (statement) {
      list_rpush(parser->statements, list_node_new(statement));
    }
    next_token(parser);
  }

  return parser->statements;
}

void next_token(struct parser_t * parser)
{
  parser->current_token = parser->peek_token;
  parser->peek_token = list_iterator_next(parser->tokens_iterator)->val;
}

int current_token_is(struct parser_t * parser, token value)
{
  return parser->current_token->type == value;
}

int peek_token_is(struct parser_t * parser, token value)
{
  return parser->peek_token->type == value;
}

int expect_peek(struct parser_t * parser, token value)
{
  if (peek_token_is(parser, value))
  {
    next_token(parser);
    return 1;
  }
  else
  {
    printf("error in %s, line %d, cursor %d: expected token %s, instead got %s\n",
      parser->peek_token->file_path, 
      parser->peek_token->line, 
      parser->peek_token->cursor,
      token_strings[value],
      token_strings[parser->peek_token->type]);
    exit(0);
    return 0;
  }
}

node * parse_statement(struct parser_t * parser)
{
  switch (parser->current_token->type)
  {
  case TOKEN_VAR: 
    return parse_variable_declaration(parser);
    break;
  case TOKEN_RETURN:
    return parse_return_statement(parser);
    break;
  default:
    return NULL;
    break;
  }
}

node * parse_variable_declaration(struct parser_t * parser)
{
  var_node * var = var_node_construct();

  if (!expect_peek(parser, TOKEN_SYMBOL)) {
    return NULL;
  }

  identifier_node * identifier = identifier_construct(parser->current_token->value);

  if (!expect_peek(parser, TOKEN_ASSIGN)) {
    return NULL;
  }

  // TODO: we're skipping expressions until we encounter a semicolon

  while (!current_token_is(parser, TOKEN_SEMI_COLON)) {
    next_token(parser);
  }

  return node_construct(var, VAR_AS_NODE);
}

node * parse_return_statement(struct parser_t * parser)
{
  return_node * return_ = return_node_construct();

  next_token(parser);

  // TODO: we're skipping expressions until we encounter a semicolon

  while (!current_token_is(parser, TOKEN_SEMI_COLON)) {
    next_token(parser);
  }

  return node_construct(return_, RETURN_AS_NODE);
}