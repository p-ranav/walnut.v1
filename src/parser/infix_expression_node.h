#ifndef INFIX_EXPRESSION_NODE_H
#define INFIX_EXPRESSION_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

typedef struct
{
  enum node_type type;    /* type = INFIX_EXPRESSION */
  node * left;
  char * operator;
  node * right;
} infix_expression_node;

infix_expression_node * infix_expression_construct();

enum node_type_t infix_expression_type(infix_expression_node * object);
void infix_expression_print(infix_expression_node * object);
void infix_expression_destruct(infix_expression_node * object);

#endif