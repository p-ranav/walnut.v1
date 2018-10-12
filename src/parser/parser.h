#ifndef PARSER_H
#define PARSER_H
#include <list.h>
#include <token.h>
#include <node.h>
#include <macros.h>
#include <block_node.h>

#include <stdio.h>
#include <stdlib.h>

/* This is the main parser struct. A collection of fields/properties that I need
   to get Pratt parsing working. This parser receives a list of tokens from 
   the lexer and tries to generate a list of 'statements'. These statements are 
   the first children of the root node of the abstract syntax tree. The lexer
   tokens can be iterated using tokens_iterator, an iterator that is initialized
   in parse(...). current_token and peek_token keep track of the current and nex
   tokens in the iteration process. 

*/
struct parser_t
{
  list_t *statements;               /* This is the parser result */
  list_iterator_t *tokens_iterator; /* iterator for lexer tokens */
  struct token_t *current_token;    /* current lexer token under examination */
  struct token_t *peek_token;       /* the token after current_token */
};

/* Entry point for the parser. We call this right after lexical analysis.
   This function takes lexer tokens as inputs and returns a list of 'statements', 
   each of which is an AST node. */
struct parser_t *parse(list_t *tokens);

/* Clean up the parser. Free up every single parsed statement, including
   sub-expressions and low-level AST nodes. */
void parser_destruct(struct parser_t *parser);

/* Print nodes in AST as statements */
void parser_print(struct parser_t *parser);

/* Helper functions for parsing */
void next_token(struct parser_t *parser);
int current_token_is(struct parser_t *parser, token value);
int peek_token_is(struct parser_t *parser, token value);
int expect_peek(struct parser_t *parser, token value);

/* Main switch case where we call either parse_variable_declaration, 
   parse_return_statement or parse_expression_statement depending
   on the context */
node *parse_statement(struct parser_t *parser);

/* Parse variable declaration statements, e.g., var x = 5;
   Build a var_node and return a node wrapper to this object
*/
node *parse_variable_declaration(struct parser_t *parser);

/* Parse return statements, e.g., return (x + y);
   Build a return_node and return a node wrapper to this object
*/
node *parse_return_statement(struct parser_t *parser);

/* Initialize hash table for pratt parsing.
   Insert into the hash table function pointers for infix/prefix expressions
   when encountering specific lexer token types. */
void pratt_table_init();

/* Clean up hash table used for pratt parsing. Simply free up the hash_array */
void pratt_table_destroy();

/* Parse expressions statements, e.g., rhs of variable declaration */
node *parse_expression_statement(struct parser_t *parser);

/* precedence enum used for Pratt parsing. Higher enum value = higher precedence */
enum precedence_t
{
  LOWEST,
  EQUAL,       /* ==, != */
  LESSGREATER, /* >, >=, < and <= */
  SUM,         /* +, - */
  PRODUCT,     /* *, /, % */
  PREFIX,      /* -X or !X */
  CALL         /* my_function(X) */
};

/* pratt parse expression
   get the prefix parser function for current token (pratt_table lookup)
   call the prefix parse function if one exists, the result is the 'left'
   of our expression. Check if the current operator is an infix operator. 
   If so, an infix parse function must exist. Find it in the pratt_table
   and updated left by calling this parse function. */
node *parse_expression(struct parser_t *parser, enum precedence_t precedence);

/* check the precedence of the peek_token */
enum precedence_t peek_precedence(struct parser_t *parser);

/* check the precedence of the current token */
enum precedence_t current_precedence(struct parser_t *parser);

/* parse identifier, construct identifier_node and return wrapper node */
node *parse_identifier(struct parser_t *parser);

/* parse integer, construct integer_node and return wrapper node */
node *parse_integer_literal(struct parser_t *parser);

/* parse float, construct float_node and return wrapper node */
node *parse_float_literal(struct parser_t *parser);

/* parse double, construct double_node and return wrapper node */
node *parse_double_literal(struct parser_t *parser);

/* parse string literal, construct string_node and return wrapper node */
node *parse_string(struct parser_t *parser);

/* parse prefix expression, construct prefix_expression_node and return wrapper node */
node *parse_prefix_expression(struct parser_t *parser);

/* parse infix expression, construct infix_expression_node and return wrapper node */
node *parse_infix_expression(struct parser_t *parser, node *left);

/* parse grouped expressions e.g., 2 + (3 + 5) * 4
   Here, (3 + 5) is a grouped expression that is evaluated with higher precedence
*/
node *parse_grouped_expression(struct parser_t *parser);

/* parse booleans - parse TOKEN_TRUE or TOKEN_FALSE, construct a bool_node
   and return a wrapped node */
node *parse_boolean(struct parser_t *parser);

/* parse if expression - check if there is an else block and optionally also
   parse else expression. return wrapped node
*/
node *parse_if_expression(struct parser_t *parser);

/* parse blocks of code, i.e., statements within { ... } curly braces
   used in if-else and while expression parsing */
block_node *parse_block_statement(struct parser_t *parser);

/* parse lambda expressions - function(<parameters>) { <list of statements> } */
node *parse_function(struct parser_t *parser);

/* parsing a lambda expression (function) requires to parse list of parameters
   This function parses a list of identifiers, e.g., a, b, c, d that is part
   of a function definition, i.e., function(a, b, c, d) { ... }
*/
void parse_function_parameters(struct parser_t *parser, list_t *parameters);

/* parse a function call, e.g., print("Hello", "World");
   treat '(' as an infix operator between an expression (identifier or function)
   and a list of arguments. Build call_node object and return wrapped node
*/
node *parse_call(struct parser_t *parser, node *function);

/* parse list of call arguments. Unlike function parameters, call arguments
   can be any expression, e.g., test(a + b, c + d) where the 2 arguments
   are expressions
*/
void parse_call_arguments(struct parser_t *parser, list_t *arguments);

#endif