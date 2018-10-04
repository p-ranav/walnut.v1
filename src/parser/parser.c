#include <parser.h>
#include <pratt_table.h>
#include <identifier_node.h>
#include <var_node.h>
#include <return_node.h>
#include <integer_node.h>
#include <prefix_expression_node.h>
#include <infix_expression_node.h>

extern const char *const token_strings[]; /* used in expect_peek */
extern node_interface *VAR_AS_NODE;
extern node_interface *RETURN_AS_NODE;
extern node_interface *IDENTIFIER_AS_NODE;
extern node_interface *INTEGER_AS_NODE;
extern node_interface *PREFIX_EXPRESSION_AS_NODE;
extern node_interface *INFIX_EXPRESSION_AS_NODE;

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

  pratt_table_init();

  /* start parsing statements */
  while (parser->peek_token && !peek_token_is(parser, TOKEN_END_OF_FILE))
  {
    node * statement = parse_statement(parser);
    if (statement) {
      list_rpush(parser->statements, list_node_new(statement));
    }
    next_token(parser);
  }

  /* print statements */
  parser_print(parser);

  return parser->statements;
}

void parser_print(struct parser_t * parser)
{
  /* use list_iterator to iterate over list of tokens */
  list_node_t * statement;
  list_iterator_t *it = list_iterator_new(parser->statements, LIST_HEAD);
  while ((statement = list_iterator_next(it)))
  {
    /* get pointer to token and print token type and value */
    node * ast_node = ((node *)statement->val);

    /* print parser AST nodes */
    node_print(ast_node);
    printf("\n");
  }
  deallocate(it);
}

void pratt_table_init()
{
  /* prefix operators */
  insert(TOKEN_SYMBOL, parse_identifier, NULL);
  insert(TOKEN_INTEGER, parse_integer_literal, NULL);
  insert(TOKEN_EXCLAMATION, parse_prefix_expression, NULL);

  /* infix operators */
  insert(TOKEN_ADD, NULL, parse_infix_expression);
  insert(TOKEN_SUBTRACT, parse_prefix_expression, parse_infix_expression);
  insert(TOKEN_MULTIPLY, NULL, parse_infix_expression);
  insert(TOKEN_DIVIDE, NULL, parse_infix_expression);
  insert(TOKEN_MODULUS, NULL, parse_infix_expression);
  insert(TOKEN_EQUAL, NULL, parse_infix_expression);
  insert(TOKEN_NOT_EQUAL, NULL, parse_infix_expression);
  insert(TOKEN_LESSER, NULL, parse_infix_expression);
  insert(TOKEN_LESSER_EQUAL, NULL, parse_infix_expression);
  insert(TOKEN_GREATER, NULL, parse_infix_expression);
  insert(TOKEN_GREATER_EQUAL, NULL, parse_infix_expression);
}

void next_token(struct parser_t * parser)
{
  parser->current_token = parser->peek_token;
  list_node_t * peek_node = list_iterator_next(parser->tokens_iterator);
  if (peek_node)
    parser->peek_token = peek_node->val;
  else
    parser->peek_token = NULL;
}

int current_token_is(struct parser_t * parser, token value)
{
  if (!parser->current_token)
    return 0;
  return parser->current_token->type == value;
}

int peek_token_is(struct parser_t * parser, token value)
{
  if (!parser->peek_token)
    return 0;
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
  if (!parser->current_token)
    return NULL;

  switch (parser->current_token->type)
  {
  case TOKEN_VAR: 
    return parse_variable_declaration(parser);
    break;
  case TOKEN_RETURN:
    return parse_return_statement(parser);
    break;
  default:
    return parse_expression_statement(parser);
    break;
  }
}

node * parse_variable_declaration(struct parser_t * parser)
{
  var_node * var = var_node_construct();

  char * identifier_name = parser->peek_token->value;
  identifier_node * identifier = identifier_construct(identifier_name);
  var->name = identifier;

  if (!expect_peek(parser, TOKEN_SYMBOL)) {
    return NULL;
  }

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

node * parse_expression_statement(struct parser_t * parser)
{
  node * expression = parse_expression(parser, LOWEST);

  if (peek_token_is(parser, TOKEN_SEMI_COLON))
    next_token(parser);

  return expression;
}

node * parse_expression(struct parser_t * parser, enum precedence_t precedence)
{
  pratt_function * current_function = search(parser->current_token->type);
  if (!current_function)
    return NULL;

  node *(*prefix)(struct parser_t *) = current_function->prefix_function;

  if (prefix == NULL)
    return NULL;

  node * left = prefix(parser);

  while (!peek_token_is(parser, TOKEN_SEMI_COLON) && precedence < peek_precedence(parser))
  {
    pratt_function * peek_function = search(parser->peek_token->type);
    if (!peek_function)
      return NULL;

    node *(*infix)(struct parser_t *, node *) = peek_function->infix_function;
    if (!infix)
      return left;

    next_token(parser);

    left = infix(parser, left);
  }

  return left;
}

enum precedence_t peek_precedence(struct parser_t * parser)
{
  token peek_token_type = parser->peek_token->type;
  return_precedence(peek_token_type);
}

enum precedence_t current_precedence(struct parser_t * parser)
{
  token current_token_type = parser->current_token->type;
  return_precedence(current_token_type);
}

node * parse_identifier(struct parser_t * parser)
{
  char * current_token_value = parser->current_token->value;
  identifier_node * identifier = identifier_construct(current_token_value);
  return node_construct(identifier, IDENTIFIER_AS_NODE);
}

node * parse_integer_literal(struct parser_t * parser)
{
  char * current_token_value = parser->current_token->value;
  int value;
  sscanf(current_token_value, "%d", &value);
  integer_node * integer = integer_construct(value);
  return node_construct(integer, INTEGER_AS_NODE);
}

node * parse_prefix_expression(struct parser_t * parser)
{
  prefix_expression_node * expression = prefix_expression_construct();
  expression->type = PREFIX_EXPRESSION;
  expression->operator = parser->current_token->value;

  next_token(parser);

  expression->right = parse_expression(parser, PREFIX);

  return node_construct(expression, PREFIX_EXPRESSION_AS_NODE);
}

node * parse_infix_expression(struct parser_t * parser, node * left)
{
  infix_expression_node * expression = infix_expression_construct();
  expression->type = INFIX_EXPRESSION;
  expression->operator = parser->current_token->value;
  expression->left = left;
  enum precedence_t precedence = current_precedence(parser);
  next_token(parser);
  expression->right = parse_expression(parser, precedence);
  return node_construct(expression, INFIX_EXPRESSION_AS_NODE);
}