#ifndef IF_EXPRESSION_NODE_H
#define IF_EXPRESSION_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>
#include <block_node.h>

typedef struct
{
  enum node_type_t type;    /* type = IF_EXPRESSION */
  node * condition;         /* condition expression */
  block_node * consequence;
  block_node * alternative;
} if_expression_node;

if_expression_node * if_expression_construct();

enum node_type_t if_expression_type(if_expression_node * object);
void if_expression_print(if_expression_node * object);
void if_expression_destruct(if_expression_node * object);

#endif