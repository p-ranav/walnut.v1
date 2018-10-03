#ifndef PARSER_H
#define PARSER_H
#include <list.h>
#include <token.h>
#include <node.h>
#include <macros.h>

#include <stdio.h>
#include <stdlib.h>

struct parser_t 
{
  list_t * statements = NULL;         /* This is the parser result */
  list_iterator_t * tokens_iterator;  /* iterator for lexer tokens */
  token * current_token;              /* current lexer token under examination */
  token * peek_token;                 /* the token after current_token */
  size_t current_token_index;         /* current index into lexer->tokens */
};

/* Entry point for the parser. 
   This function takes lexer tokens as inputs
   and returns a list of 'statements', 
   each of which is an AST node. */
list_t * parse(list_t * tokens);

/* Helper functions for parsing */
void next_token(struct parser_t * parser);

node * parse_statement(struct parser_t * parser);
node * parse_variable_declaration(struct parser_t * parser);

#endif