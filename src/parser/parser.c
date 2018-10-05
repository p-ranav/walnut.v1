#include <parser.h>
#include <pratt_table.h>
#include <identifier_node.h>
#include <var_node.h>
#include <return_node.h>
#include <integer_node.h>
#include <prefix_expression_node.h>
#include <infix_expression_node.h>
#include <bool_node.h>
#include <block_node.h>
#include <if_expression_node.h>
#include <function_node.h>
#include <call_node.h>

extern const char *const token_strings[]; /* used in expect_peek */
extern node_interface *RETURN_AS_NODE;
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
  insert(TOKEN_TRUE, parse_boolean, NULL);
  insert(TOKEN_FALSE, parse_boolean, NULL);
  insert(TOKEN_LEFT_PARANTHESIS, parse_grouped_expression, parse_call);
  insert(TOKEN_IF, parse_if_expression, NULL);
  insert(TOKEN_FUNCTION, parse_function, NULL);

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

  next_token(parser);

  var->expression = parse_expression(parser, LOWEST);

  if (peek_token_is(parser, TOKEN_SEMI_COLON))
    next_token(parser);

  node_interface *VAR_AS_NODE = allocate(node_interface, 1);
  VAR_AS_NODE->type = (enum node_type_t(*)(void *)) var_node_type;
  VAR_AS_NODE->print = (void(*)(void*)) var_node_print;
  VAR_AS_NODE->destruct = (void(*)(void *)) var_node_destruct;
  return node_construct(var, VAR_AS_NODE);
}

node * parse_return_statement(struct parser_t * parser)
{
  return_node * return_ = return_node_construct();

  next_token(parser);

  return_->expression = parse_expression(parser, LOWEST);

  if (peek_token_is(parser, TOKEN_SEMI_COLON))
    next_token(parser);

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

  node_interface *IDENTIFIER_AS_NODE = allocate(node_interface, 1);
  IDENTIFIER_AS_NODE->type = (enum node_type_t(*)(void *)) identifier_type;
  IDENTIFIER_AS_NODE->print = (void(*)(void*)) identifier_print;
  IDENTIFIER_AS_NODE->destruct = (void(*)(void *)) identifier_destruct;
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

node * parse_boolean(struct parser_t * parser)
{
  bool_node * boolean = bool_construct(current_token_is(parser, TOKEN_TRUE));

  node_interface *BOOLEAN_AS_NODE = allocate(node_interface, 1);
  BOOLEAN_AS_NODE->type = (enum node_type_t(*)(void *)) bool_type;
  BOOLEAN_AS_NODE->print = (void(*)(void*)) bool_print;
  BOOLEAN_AS_NODE->destruct = (void(*)(void *)) bool_destruct;

  return node_construct(boolean, BOOLEAN_AS_NODE);
}

node * parse_grouped_expression(struct parser_t * parser)
{
  next_token(parser);

  node * expression = parse_expression(parser, LOWEST);

  if (!expect_peek(parser, TOKEN_RIGHT_PARANTHESIS))
    return NULL;

  return expression;
}

node * parse_if_expression(struct parser_t * parser)
{
  if_expression_node * if_expression = if_expression_construct();

  if (!expect_peek(parser, TOKEN_LEFT_PARANTHESIS))
    return NULL;

  next_token(parser);
  if_expression->condition = parse_expression(parser, LOWEST);

  if (!expect_peek(parser, TOKEN_RIGHT_PARANTHESIS))
    return NULL;

  if (!expect_peek(parser, TOKEN_LEFT_CURLY))
    return NULL;

  if_expression->consequence = parse_block_statement(parser);

  if (peek_token_is(parser, TOKEN_ELSE))
  {
    next_token(parser);

    if (!expect_peek(parser, TOKEN_LEFT_CURLY))
      return NULL;

    if_expression->alternative = parse_block_statement(parser);
  }

  node_interface *IF_EXPRESSION_AS_NODE = allocate(node_interface, 1);
  IF_EXPRESSION_AS_NODE->type = (enum node_type_t(*)(void *)) if_expression_type;
  IF_EXPRESSION_AS_NODE->print = (void(*)(void*)) if_expression_print;
  IF_EXPRESSION_AS_NODE->destruct = (void(*)(void *)) if_expression_destruct;
  return node_construct(if_expression, IF_EXPRESSION_AS_NODE);
}

block_node * parse_block_statement(struct parser_t * parser)
{
  block_node * block = block_construct();

  next_token(parser);

  while (parser->current_token && !current_token_is(parser, TOKEN_RIGHT_CURLY) && !current_token_is(parser, TOKEN_END_OF_FILE))
  {
    node * statement = parse_statement(parser);
    if (statement) {
      list_rpush(block->statements, list_node_new(statement));
    }
    next_token(parser);
  }

  return block;
}

node * parse_function(struct parser_t * parser)
{
  function_node * function = function_construct();
  
  if (!expect_peek(parser, TOKEN_LEFT_PARANTHESIS))
  {
    return NULL;
  }

  parse_function_parameters(parser, function->parameters);

  if (!expect_peek(parser, TOKEN_LEFT_CURLY)) {
    return NULL;
  }

  function->body = parse_block_statement(parser);

  node_interface *FUNCTION_AS_NODE = allocate(node_interface, 1);
  FUNCTION_AS_NODE->type = (enum node_type_t(*)(void *)) function_type;
  FUNCTION_AS_NODE->print = (void(*)(void*)) function_print;
  FUNCTION_AS_NODE->destruct = (void(*)(void *)) function_destruct;
  return node_construct(function, FUNCTION_AS_NODE);
}

void parse_function_parameters(struct parser_t * parser, list_t * parameters) {
  if (parser->peek_token && peek_token_is(parser, TOKEN_RIGHT_PARANTHESIS)) {
    next_token(parser);
    return;
  }

  next_token(parser);

  identifier_node * parameter = identifier_construct(parser->current_token->value);
  list_rpush(parameters, list_node_new(parameter));

  while (parser->peek_token && peek_token_is(parser, TOKEN_COMMA)) {
    next_token(parser);
    next_token(parser);
    identifier_node * parameter = identifier_construct(parser->current_token->value);
    list_rpush(parameters, list_node_new(parameter));
  }

  if (!expect_peek(parser, TOKEN_RIGHT_PARANTHESIS))
    return;
}

node * parse_call(struct parser_t * parser, node * function)
{
  call_node * call = call_construct();
  call->function = function;
  parse_call_arguments(parser, call->arguments);

  node_interface *CALL_AS_NODE = allocate(node_interface, 1);
  CALL_AS_NODE->type = (enum node_type_t(*)(void *)) call_type;
  CALL_AS_NODE->print = (void(*)(void*)) call_print;
  CALL_AS_NODE->destruct = (void(*)(void *)) call_destruct;
  return node_construct(call, CALL_AS_NODE);
}

void parse_call_arguments(struct parser_t * parser, list_t * arguments)
{
  if (peek_token_is(parser, TOKEN_RIGHT_PARANTHESIS)) {
    next_token(parser);
    return;
  }

  next_token(parser);
  list_rpush(arguments, list_node_new(parse_expression(parser, LOWEST)));

  while (parser->peek_token && peek_token_is(parser, TOKEN_COMMA)) {
    next_token(parser);
    next_token(parser);
    list_rpush(arguments, list_node_new(parse_expression(parser, LOWEST)));
  }

  if (!expect_peek(parser, TOKEN_RIGHT_PARANTHESIS))
    return;
}