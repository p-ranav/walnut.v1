#ifndef PARSER_H
#define PARSER_H
#include <list.h>
#include <token.h>
#include <node.h>

/* Entry point for the parser. 
   This function takes lexer tokens as inputs
   and returns a list of 'statements', 
   each of which is an AST node. */
list_t * parse(list_t * tokens);

/* Helper functions for parsing */
void next_token(token * current_token, token * peek_token, list_iterator_t * iterator);

#endif