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
  list_t * statements;                /* This is the parser result */
  list_iterator_t * tokens_iterator;  /* iterator for lexer tokens */
  struct token_t * current_token;     /* current lexer token under examination */
  struct token_t * peek_token;        /* the token after current_token */
};

/* Entry point for the parser. 
   This function takes lexer tokens as inputs
   and returns a list of 'statements', 
   each of which is an AST node. */
struct parser_t * parse(list_t * tokens);

void parser_destruct(struct parser_t * parser);

/* Print nodes in AST */
void parser_print(struct parser_t * parser);

/* Helper functions for parsing */
void next_token(struct parser_t * parser);
int current_token_is(struct parser_t * parser, token value);
int peek_token_is(struct parser_t * parser, token value);
int expect_peek(struct parser_t * parser, token value);

node * parse_statement(struct parser_t * parser);
node * parse_variable_declaration(struct parser_t * parser);
node * parse_return_statement(struct parser_t * parser);

void pratt_table_init();
void pratt_table_destroy();
node * parse_expression_statement(struct parser_t * parser);

enum precedence_t {
  LOWEST,
  EQUAL,        /* == */
  LESSGREATER,  /* > or < */
  SUM,          /* + */
  PRODUCT,      /* * */
  PREFIX,       /* -X or !X */
  CALL          /* my_function(X) */
};

node * parse_expression(struct parser_t * parser, enum precedence_t precedence);

/* Infix operator helper functions */
enum precedence_t peek_precedence(struct parser_t * parser);
enum precedence_t current_precedence(struct parser_t * parser);

node * parse_identifier(struct parser_t * parser);
node * parse_integer_literal(struct parser_t * parser);
node * parse_float_literal(struct parser_t * parser);
node * parse_double_literal(struct parser_t * parser);
node * parse_string(struct parser_t * parser);
node * parse_prefix_expression(struct parser_t * parser);
node * parse_infix_expression(struct parser_t * parser, node * left);
node * parse_grouped_expression(struct parser_t * parser);
node * parse_boolean(struct parser_t * parser);
node * parse_if_expression(struct parser_t * parser);
block_node * parse_block_statement(struct parser_t * parser);
node * parse_function(struct parser_t * parser);
void parse_function_parameters(struct parser_t * parser, list_t * parameters);
node * parse_call(struct parser_t * parser, node * function);
void parse_call_arguments(struct parser_t * parser, list_t * arguments);

#endif