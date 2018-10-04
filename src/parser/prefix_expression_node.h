#ifndef PREFIX_EXPRESSION_NODE_H
#define PREFIX_EXPRESSION_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

typedef struct
{
  enum node_type type;    /* type = PREFIX_EXPRESSION */
  char * operator;
  node * right;
} prefix_expression_node;

prefix_expression_node * prefix_expression_construct();

enum node_type_t prefix_expression_type(prefix_expression_node * object);
void prefix_expression_print(prefix_expression_node * object);
void prefix_expression_destruct(prefix_expression_node * object);

#endif