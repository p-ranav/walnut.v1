#include <prefix_expression_node.h>
#include <stdio.h>
#include <stdlib.h>

node_interface *PREFIX_EXPRESSION_AS_NODE = &(node_interface)
{
  .type = (enum node_type_t(*)(void *)) prefix_expression_type,
    .print = (void(*)(void*)) prefix_expression_print,
    .destruct = (void(*)(void *)) prefix_expression_destruct
};

prefix_expression_node * prefix_expression_construct()
{
  prefix_expression_node * object = allocate(prefix_expression_node, 1);
  object->type = PREFIX_EXPRESSION;
  return object;
}

enum node_type_t prefix_expression_type(prefix_expression_node * object)
{
  return PREFIX_EXPRESSION;
}

void prefix_expression_print(prefix_expression_node * object)
{
  printf("(");
  printf("%s", object->operator);
  node_print(object->right);
  printf(")");
}

void prefix_expression_destruct(prefix_expression_node * object)
{
  free(object);
}