#include <parser.h>
#include <pratt_table.h>
#include <identifier_node.h>
#include <var_node.h>
#include <return_node.h>
#include <integer_node.h>
#include <float_node.h>
#include <double_node.h>
#include <string_node.h>
#include <prefix_expression_node.h>
#include <infix_expression_node.h>
#include <bool_node.h>
#include <block_node.h>
#include <if_expression_node.h>
#include <function_node.h>
#include <call_node.h>

extern const char *const token_strings[]; /* used in expect_peek */

struct parser_t *parse(list_t *tokens)
{
  struct parser_t *parser = allocate(struct parser_t, 1);
  parser->statements = list_new();

  /* initialize token iterator */
  parser->tokens_iterator = list_iterator_new(tokens, LIST_HEAD);

  /* initialize current_token and peek_token */
  parser->current_token = NULL;
  parser->peek_token = NULL;

  /* make sure current_token and peek_token are initialized */
  next_token(parser);
  next_token(parser);

  pratt_table_init();

  /* start parsing statements */
  while (parser->peek_token && !peek_token_is(parser, TOKEN_END_OF_FILE))
  {
    node *statement = parse_statement(parser);
    if (statement)
    {
      list_rpush(parser->statements, list_node_new(statement));
    }
    next_token(parser);
  }

  return parser;
}

void parser_print(struct parser_t *parser)
{
  /* use list_iterator to iterate over list of tokens */
  list_node_t *statement;
  list_iterator_t *it = list_iterator_new(parser->statements, LIST_HEAD);
  while ((statement = list_iterator_next(it)))
  {
    /* get pointer to token and print token type and value */
    node *ast_node = ((node *)statement->val);

    /* print parser AST nodes */
    node_print(ast_node);
    printf("\n");
  }
  deallocate(it);
}

void parser_destruct(struct parser_t *parser)
{
  /* declarations */
  list_node_t *statement;
  list_iterator_t *it;
  node *ast_node;

  pratt_table_destroy();

  /* use list_iterator to iterate over list of tokens */
  it = list_iterator_new(parser->statements, LIST_HEAD);
  while ((statement = list_iterator_next(it)))
  {
    /* get pointer to token and free */
    ast_node = ((node *)statement->val);

    /* free AST nodes */
    node_destruct(ast_node);
  }
  deallocate(it);
  free(parser->tokens_iterator);
  list_destroy(parser->statements);
  free(parser);
}

void pratt_table_init()
{
  /* prefix operators */
  insert(TOKEN_SYMBOL, parse_identifier, NULL);
  insert(TOKEN_INTEGER, parse_integer_literal, NULL);
  insert(TOKEN_FLOAT, parse_float_literal, NULL);
  insert(TOKEN_DOUBLE, parse_double_literal, NULL);
  insert(TOKEN_STRING_LITERAL, parse_string, NULL);
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

void pratt_table_destroy()
{
  /* prefix operators */
  delete_item(TOKEN_SYMBOL);
  delete_item(TOKEN_INTEGER);
  delete_item(TOKEN_FLOAT);
  delete_item(TOKEN_DOUBLE);
  delete_item(TOKEN_STRING_LITERAL);
  delete_item(TOKEN_EXCLAMATION);
  delete_item(TOKEN_TRUE);
  delete_item(TOKEN_FALSE);
  delete_item(TOKEN_LEFT_PARANTHESIS);
  delete_item(TOKEN_IF);
  delete_item(TOKEN_FUNCTION);

  /* infix operators */
  delete_item(TOKEN_ADD);
  delete_item(TOKEN_SUBTRACT);
  delete_item(TOKEN_MULTIPLY);
  delete_item(TOKEN_DIVIDE);
  delete_item(TOKEN_MODULUS);
  delete_item(TOKEN_EQUAL);
  delete_item(TOKEN_NOT_EQUAL);
  delete_item(TOKEN_LESSER);
  delete_item(TOKEN_LESSER_EQUAL);
  delete_item(TOKEN_GREATER);
  delete_item(TOKEN_GREATER_EQUAL);
}

void next_token(struct parser_t *parser)
{
  /* declarations */
  list_node_t *peek_node;

  parser->current_token = parser->peek_token;
  peek_node = list_iterator_next(parser->tokens_iterator);
  if (peek_node)
    parser->peek_token = peek_node->val;
  else
    parser->peek_token = NULL;
}

int current_token_is(struct parser_t *parser, token value)
{
  if (!parser->current_token)
    return 0;
  return parser->current_token->type == value;
}

int peek_token_is(struct parser_t *parser, token value)
{
  if (!parser->peek_token)
    return 0;
  return parser->peek_token->type == value;
}

int expect_peek(struct parser_t *parser, token value)
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

node *parse_statement(struct parser_t *parser)
{
  /* if current token is NULL, there's nothing to parse */
  if (!parser->current_token)
    return NULL;

  /* check if current token is X and call parse_X appropriately */
  switch (parser->current_token->type)
  {
  case TOKEN_VAR:
    /* parse variable declarations */
    return parse_variable_declaration(parser);
    break;
  case TOKEN_RETURN:
    /* parse return statements */
    return parse_return_statement(parser);
    break;
  default:
    /* parse general infix or prefix expressions */
    return parse_expression_statement(parser);
    break;
  }
}

node *parse_variable_declaration(struct parser_t *parser)
{
  /* declarations */
  var_node *var;
  char *identifier_name;
  identifier_node *identifier;
  node_interface *VAR_AS_NODE;

  /* construct a var_node */
  var = var_node_construct();

  /* save the name of the identifier */
  identifier_name = parser->peek_token->value;
  identifier = identifier_construct(identifier_name);
  var->name = identifier;

  /* peek (which we just saved above) is a SYMBOL. Confirm this */
  if (!expect_peek(parser, TOKEN_SYMBOL))
  {
    return NULL;
  }

  /* after the identifier comes the '=' token */
  if (!expect_peek(parser, TOKEN_ASSIGN))
  {
    return NULL;
  }

  /* get past the '=' sign */
  next_token(parser);

  /* parse and save the RHS of variable declaration - This is an expression */
  var->expression = parse_expression(parser, LOWEST);

  /* check if expression parsing is done and we're at ';'. If so, move up by 1 token */
  if (peek_token_is(parser, TOKEN_SEMI_COLON))
    next_token(parser);

  /* the following code is equivalent to the C++ code:
     node * ptr = new var_node(...);
     we're constructing a node pointer and wrapping the parsed variable declaration 
  */
  VAR_AS_NODE = allocate(node_interface, 1);
  VAR_AS_NODE->type = (enum node_type_t(*)(void *))var_node_type;
  VAR_AS_NODE->print = (void (*)(void *))var_node_print;
  VAR_AS_NODE->destruct = (void (*)(void *))var_node_destruct;
  return node_construct(var, VAR_AS_NODE);
}

node *parse_return_statement(struct parser_t *parser)
{
  /* declarations */
  return_node *return_;
  node_interface *RETURN_AS_NODE;

  /* construct a return_node object */
  return_ = return_node_construct();

  /* we're here because the current_token is KEYWORD_RETURN. Move up 1 token */
  next_token(parser);

  /* parse the expression right after the 'return' keyword */
  return_->expression = parse_expression(parser, LOWEST);

  /* check that the peek_token is ';' and move up 1 token */
  if (peek_token_is(parser, TOKEN_SEMI_COLON))
    next_token(parser);

  /* the following code is equivalent to the C++ code:
     node * ptr = new return_node(...);
     we're constructing a node pointer and wrapping the parsed return statement
  */
  RETURN_AS_NODE = allocate(node_interface, 1);
  RETURN_AS_NODE->type = (enum node_type_t(*)(void *))return_node_type;
  RETURN_AS_NODE->print = (void (*)(void *))return_node_print;
  RETURN_AS_NODE->destruct = (void (*)(void *))return_node_destruct;
  return node_construct(return_, RETURN_AS_NODE);
}

node *parse_expression_statement(struct parser_t *parser)
{
  /* declaratiosn */
  node *expression;

  /* parse general expression. Typical Pratt parsing here */
  expression = parse_expression(parser, LOWEST);

  /* check if the next token is ';' and move up */
  if (peek_token_is(parser, TOKEN_SEMI_COLON))
    next_token(parser);

  return expression;
}

node *parse_expression(struct parser_t *parser, enum precedence_t precedence)
{
  /* declarations */
  pratt_function *current_function;
  node *(*prefix)(struct parser_t *);
  node *left;
  pratt_function *peek_function;
  node *(*infix)(struct parser_t *, node *);

  /* get the prefix parse function for the current token. pratt_table lookup */
  current_function = search(parser->current_token->type);
  if (!current_function)
    return NULL;
  prefix = current_function->prefix_function;

  if (prefix == NULL)
    return NULL;

  /* call the prefix parse function and obtain the 'left' of our expression */
  left = prefix(parser);

  /* Loop until ';' and as long as the current precedence is less than peek precedence  */
  while (!peek_token_is(parser, TOKEN_SEMI_COLON) && precedence < peek_precedence(parser))
  {
    /* get the infix parse function for the current token. pratt_table lookup */
    peek_function = search(parser->peek_token->type);
    if (!peek_function)
      return NULL;

    infix = peek_function->infix_function;

    /* check if an infix parse function is defined, e.g., for '-', '!' etc. */
    if (!infix)
      return left;

    next_token(parser);

    /* update left by calling the appropriate infix parse function */
    left = infix(parser, left);
  }

  return left;
}

enum precedence_t peek_precedence(struct parser_t *parser)
{
  /* declarations */
  token peek_token_type;

  /* return precedence of peek token. Apologies for macro */
  peek_token_type = parser->peek_token->type;
  return_precedence(peek_token_type);
}

enum precedence_t current_precedence(struct parser_t *parser)
{
  /* declarations */
  token current_token_type;

  /* return precedence of current token. Apologies for macro */
  current_token_type = parser->current_token->type;
  return_precedence(current_token_type);
}

node *parse_identifier(struct parser_t *parser)
{
  /* declarations */
  char *current_token_value;
  identifier_node *identifier;
  node_interface *IDENTIFIER_AS_NODE;

  current_token_value = parser->current_token->value;
  identifier = identifier_construct(current_token_value);

  /* the following code is equivalent to the C++ code:
     node * ptr = new identifier_node(...);
     we're constructing a node pointer and wrapping the parsed identifier
  */
  IDENTIFIER_AS_NODE = allocate(node_interface, 1);
  IDENTIFIER_AS_NODE->type = (enum node_type_t(*)(void *))identifier_type;
  IDENTIFIER_AS_NODE->print = (void (*)(void *))identifier_print;
  IDENTIFIER_AS_NODE->destruct = (void (*)(void *))identifier_destruct;
  return node_construct(identifier, IDENTIFIER_AS_NODE);
}

node *parse_integer_literal(struct parser_t *parser)
{
  /* declarations */
  char *current_token_value;
  int value;
  integer_node *integer;
  node_interface *INTEGER_AS_NODE;

  /* Convert string value to integer with sscanf */
  current_token_value = parser->current_token->value;
  sscanf(current_token_value, "%d", &value);

  /* construct an integer_node with scanned int value */
  integer = integer_construct(value);

  /* the following code is equivalent to the C++ code:
     node * ptr = new integer_node(...);
     we're constructing a node pointer and wrapping the parsed integer
  */
  INTEGER_AS_NODE = allocate(node_interface, 1);
  INTEGER_AS_NODE->type = (enum node_type_t(*)(void *))integer_type;
  INTEGER_AS_NODE->print = (void (*)(void *))integer_print;
  INTEGER_AS_NODE->destruct = (void (*)(void *))integer_destruct;
  return node_construct(integer, INTEGER_AS_NODE);
}

node *parse_float_literal(struct parser_t *parser)
{
  /* declarations */
  char *current_token_value;
  float value;
  float_node *float_;
  node_interface *FLOAT_AS_NODE;

  /* Use sscanf to convert parsed string to float value */
  current_token_value = parser->current_token->value;
  sscanf(current_token_value, "%f", &value);
  float_ = float_construct(value);

  /* the following code is equivalent to the C++ code:
     node * ptr = new float_node(...);
     we're constructing a node pointer and wrapping the parsed float
  */
  FLOAT_AS_NODE = allocate(node_interface, 1);
  FLOAT_AS_NODE->type = (enum node_type_t(*)(void *))float_type;
  FLOAT_AS_NODE->print = (void (*)(void *))float_print;
  FLOAT_AS_NODE->destruct = (void (*)(void *))float_destruct;
  return node_construct(float_, FLOAT_AS_NODE);
}

node *parse_double_literal(struct parser_t *parser)
{
  /* declarations */
  char *current_token_value;
  double value;
  double_node *double_;
  node_interface *DOUBLE_AS_NODE;

  /* Use sscanf to convert parsed string to double value
     Unlike printf, %f does not promote to double in sscanf. Hence %lf
  */
  current_token_value = parser->current_token->value;
  sscanf(current_token_value, "%lf", &value);
  double_ = double_construct(value);

  /* the following code is equivalent to the C++ code:
     node * ptr = new double_node(...);
     we're constructing a node pointer and wrapping the parsed double
  */
  DOUBLE_AS_NODE = allocate(node_interface, 1);
  DOUBLE_AS_NODE->type = (enum node_type_t(*)(void *))double_type;
  DOUBLE_AS_NODE->print = (void (*)(void *))double_print;
  DOUBLE_AS_NODE->destruct = (void (*)(void *))double_destruct;
  return node_construct(double_, DOUBLE_AS_NODE);
}

node *parse_string(struct parser_t *parser)
{
  /* declarations */
  char *current_token_value;
  string_node *string;
  node_interface *STRING_AS_NODE;

  /* Pass current_token->value to string construct and build a string node */
  current_token_value = parser->current_token->value;
  string = string_construct(current_token_value);

  /* the following code is equivalent to the C++ code:
     node * ptr = new string_node(...);
     we're constructing a node pointer and wrapping the parsed string literal
  */
  STRING_AS_NODE = allocate(node_interface, 1);
  STRING_AS_NODE->type = (enum node_type_t(*)(void *))string_type;
  STRING_AS_NODE->print = (void (*)(void *))string_print;
  STRING_AS_NODE->destruct = (void (*)(void *))string_destruct;
  return node_construct(string, STRING_AS_NODE);
}

node *parse_prefix_expression(struct parser_t *parser)
{
  /* declarations */
  prefix_expression_node *expression;
  node_interface *PREFIX_EXPRESSION_AS_NODE;

  /* construct a prefix expression */
  expression = prefix_expression_construct(parser->current_token->value);
  expression->type = PREFIX_EXPRESSION;

  next_token(parser);

  /* There's no left. Parse right and move on */
  expression->right = parse_expression(parser, PREFIX);

  /* the following code is equivalent to the C++ code:
     node * ptr = new prefix_expression_node(...);
     we're constructing a node pointer and wrapping the parsed prefix expression
  */
  PREFIX_EXPRESSION_AS_NODE = allocate(node_interface, 1);
  PREFIX_EXPRESSION_AS_NODE->type = (enum node_type_t(*)(void *))prefix_expression_type;
  PREFIX_EXPRESSION_AS_NODE->print = (void (*)(void *))prefix_expression_print;
  PREFIX_EXPRESSION_AS_NODE->destruct = (void (*)(void *))prefix_expression_destruct;
  return node_construct(expression, PREFIX_EXPRESSION_AS_NODE);
}

node *parse_infix_expression(struct parser_t *parser, node *left)
{
  /* declarations */
  infix_expression_node *expression;
  enum precedence_t precedence;
  node_interface *INFIX_EXPRESSION_AS_NODE;

  /* When parsing an infix operator, the expression to the right of the operator
     if passed as argument (this is what left represents). Construct a new
     infix expression node and save this 'left'. 
  */
  expression = infix_expression_construct(parser->current_token->value);
  expression->type = INFIX_EXPRESSION;
  /* save left */
  expression->left = left;

  /* get the precedence of current operator and parse the right expression
     pass the current_precedence so the parser knows how to group expressions
  */
  precedence = current_precedence(parser);
  next_token(parser);
  expression->right = parse_expression(parser, precedence);

  /* the following code is equivalent to the C++ code:
     node * ptr = new infix_expression_node(...);
     we're constructing a node pointer and wrapping the parsed infix expression
  */
  INFIX_EXPRESSION_AS_NODE = allocate(node_interface, 1);
  INFIX_EXPRESSION_AS_NODE->type = (enum node_type_t(*)(void *))infix_expression_type;
  INFIX_EXPRESSION_AS_NODE->print = (void (*)(void *))infix_expression_print;
  INFIX_EXPRESSION_AS_NODE->destruct = (void (*)(void *))infix_expression_destruct;
  return node_construct(expression, INFIX_EXPRESSION_AS_NODE);
}

node *parse_boolean(struct parser_t *parser)
{
  /* declarations */
  bool_node *boolean;
  node_interface *BOOLEAN_AS_NODE;

  /* construct boolean and set it to true if current token is TOKEN_TRUE */
  boolean = bool_construct(current_token_is(parser, TOKEN_TRUE));

  /* the following code is equivalent to the C++ code:
     node * ptr = new bool_node(...);
     we're constructing a node pointer and wrapping the parsed boolean
  */
  BOOLEAN_AS_NODE = allocate(node_interface, 1);
  BOOLEAN_AS_NODE->type = (enum node_type_t(*)(void *))bool_type;
  BOOLEAN_AS_NODE->print = (void (*)(void *))bool_print;
  BOOLEAN_AS_NODE->destruct = (void (*)(void *))bool_destruct;

  return node_construct(boolean, BOOLEAN_AS_NODE);
}

node *parse_grouped_expression(struct parser_t *parser)
{
  /* declarations */
  node *expression;

  /* expressions are grouped with '('. Get past this and start parsing */
  next_token(parser);

  /* there's nothing to the left of '(' - parse with LOWEST */
  expression = parse_expression(parser, LOWEST);

  /* there better be a ')' when we're done. Check this */
  if (!expect_peek(parser, TOKEN_RIGHT_PARANTHESIS))
    return NULL;

  return expression;
}

node *parse_if_expression(struct parser_t *parser)
{
  /* declarations */
  if_expression_node *if_expression;
  node_interface *IF_EXPRESSION_AS_NODE;

  if_expression = if_expression_construct();

  /* We're at TOKEN_IF. What's next? Well ofcourse its '(' */
  if (!expect_peek(parser, TOKEN_LEFT_PARANTHESIS))
    return NULL;

  /* get past '(' */
  next_token(parser);

  /* parse the if condition */
  if_expression->condition = parse_expression(parser, LOWEST);

  /* we better be at ')' since we just parsed the if (<condition>)
                                                                 ^
  */
  if (!expect_peek(parser, TOKEN_RIGHT_PARANTHESIS))
    return NULL;

  /* Now we expect the open curly '{' */
  if (!expect_peek(parser, TOKEN_LEFT_CURLY))
    return NULL;

  /* parse block of code until closed curly '}' */
  if_expression->consequence = parse_block_statement(parser);

  /* TODO: check if peek token is TOKEN_ELSE_IF
     make a recursive call to parse_if_expression and save as
     conditional_alternative in the current if_expression variable
  */

  /* check if there is an else block */
  if (peek_token_is(parser, TOKEN_ELSE))
  {
    /* check past the else keyword - there's no condition here */
    next_token(parser);

    /* else has no condition. check if peek is '{' */
    if (!expect_peek(parser, TOKEN_LEFT_CURLY))
      return NULL;

    /* parse the else block of code */
    if_expression->alternative = parse_block_statement(parser);
  }

  /* the following code is equivalent to the C++ code:
     node * ptr = new if_expression_node(...);
     we're constructing a node pointer and wrapping the parsed if expression
  */
  IF_EXPRESSION_AS_NODE = allocate(node_interface, 1);
  IF_EXPRESSION_AS_NODE->type = (enum node_type_t(*)(void *))if_expression_type;
  IF_EXPRESSION_AS_NODE->print = (void (*)(void *))if_expression_print;
  IF_EXPRESSION_AS_NODE->destruct = (void (*)(void *))if_expression_destruct;
  return node_construct(if_expression, IF_EXPRESSION_AS_NODE);
}

block_node *parse_block_statement(struct parser_t *parser)
{
  /* declarations */
  block_node *block;
  node *statement;

  /* initialize block_node to be returned */
  block = block_construct();

  /* we're at '{' Let's get past this and start parsing statements */
  next_token(parser);

  /* loop until closed curly '}' and parse statements */
  while (parser->current_token && !current_token_is(parser, TOKEN_RIGHT_CURLY) && !current_token_is(parser, TOKEN_END_OF_FILE))
  {
    /* parse_statement(...) already exists and does a great job. Lets use it. */
    statement = parse_statement(parser);
    if (statement)
    {
      list_rpush(block->statements, list_node_new(statement));
    }
    /* get past semi_colon */
    next_token(parser);
  }

  return block;
}

node *parse_function(struct parser_t *parser)
{
  /* declarations */
  function_node *function;
  node_interface *FUNCTION_AS_NODE;

  /* initialize function node */
  function = function_construct();

  /* we're at the keyword 'function' (TOKEN_FUNCTION). Now we expect to see '(' */
  if (!expect_peek(parser, TOKEN_LEFT_PARANTHESIS))
    return NULL;

  /* parse our list of function parameters - we expect these to be identifiers */
  parse_function_parameters(parser, function->parameters);

  /* We're done parsing our list of function parameters. Now we expect to see '{' */
  if (!expect_peek(parser, TOKEN_LEFT_CURLY))
  {
    return NULL;
  }

  /* parse block of code - just like in if_expression parsing */
  function->body = parse_block_statement(parser);

  /* the following code is equivalent to the C++ code:
     node * ptr = new function_node(...);
     we're constructing a node pointer and wrapping the parsed function
  */
  FUNCTION_AS_NODE = allocate(node_interface, 1);
  FUNCTION_AS_NODE->type = (enum node_type_t(*)(void *))function_type;
  FUNCTION_AS_NODE->print = (void (*)(void *))function_print;
  FUNCTION_AS_NODE->destruct = (void (*)(void *))function_destruct;
  return node_construct(function, FUNCTION_AS_NODE);
}

void parse_function_parameters(struct parser_t *parser, list_t *parameters)
{
  /* declarations */
  identifier_node *parameter;

  /* if the next token is ')', this function has no parameters. Move up and return */
  if (parser->peek_token && peek_token_is(parser, TOKEN_RIGHT_PARANTHESIS))
  {
    next_token(parser);
    return;
  }

  /* if we're here, there are parameters to parse. Get past the open paranthesis '(' */
  next_token(parser);

  /* construct an identifier with current_token value */
  parameter = identifier_construct(parser->current_token->value);
  list_rpush(parameters, list_node_new(parameter));

  /* if the next token is a ',' there are more identifiers (parameters) to parse. LOOP! */
  while (parser->peek_token && peek_token_is(parser, TOKEN_COMMA))
  {
    /* get past current identifier*/
    next_token(parser);

    /* get past the comma ',' */
    next_token(parser);

    /* parse next identifier */
    parameter = identifier_construct(parser->current_token->value);
    list_rpush(parameters, list_node_new(parameter));
  }

  /* we're at the end. confirm that the next token is the right paranthesis ')' */
  if (!expect_peek(parser, TOKEN_RIGHT_PARANTHESIS))
    return;
}

node *parse_call(struct parser_t *parser, node *function)
{
  /* parsing a call is actually an infix expression - <function_name> ( <arguments> ...
     Here, the open paranthesis '(' is the infix operator and the argument
     to this function, parse_call, is the 'left' of the infix expression
  */

  /* declarations */
  call_node *call;
  node_interface *CALL_AS_NODE;

  /* Construct a call_node and save the left expression as the function */
  call = call_construct();
  call->function = function;

  /* Parse comma-separated call arguments. Unlike function parameters, call arguments
     can be any expression (not just identifiers)
  */
  parse_call_arguments(parser, call->arguments);

  /* the following code is equivalent to the C++ code:
     node * ptr = new call_node(...);
     we're constructing a node pointer and wrapping the parsed function call
  */
  CALL_AS_NODE = allocate(node_interface, 1);
  CALL_AS_NODE->type = (enum node_type_t(*)(void *))call_type;
  CALL_AS_NODE->print = (void (*)(void *))call_print;
  CALL_AS_NODE->destruct = (void (*)(void *))call_destruct;
  return node_construct(call, CALL_AS_NODE);
}

void parse_call_arguments(struct parser_t *parser, list_t *arguments)
{
  /* we're here because there was a function and we need to parse the arguments
     if the next token is the closed paranthesis ')' then the call takes no arguments
  */
  if (peek_token_is(parser, TOKEN_RIGHT_PARANTHESIS))
  {
    next_token(parser);
    return;
  }

  /* get past the '(' and parse expression. 
     Remember, each argument is an expression - not just an identifier
  */
  next_token(parser);
  list_rpush(arguments, list_node_new(parse_expression(parser, LOWEST)));

  /* check if there's a comma. If so, there are more arguments to parse */
  while (parser->peek_token && peek_token_is(parser, TOKEN_COMMA))
  {
    /* get past current argument */
    next_token(parser);

    /* get past the comma */
    next_token(parser);

    /* parse next argument and repeat */
    list_rpush(arguments, list_node_new(parse_expression(parser, LOWEST)));
  }

  /* we're at the end. Expect the closed paranthesis ')' */
  if (!expect_peek(parser, TOKEN_RIGHT_PARANTHESIS))
    return;
}