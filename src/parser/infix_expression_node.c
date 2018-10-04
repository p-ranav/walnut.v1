#include <infix_expression_node.h>
#include <stdio.h>
#include <stdlib.h>

node_interface *INFIX_EXPRESSION_AS_NODE = &(node_interface)
{
  .type = (enum node_type_t(*)(void *)) infix_expression_type,
    .print = (void(*)(void*)) infix_expression_print,
    .destruct = (void(*)(void *)) infix_expression_destruct
};

infix_expression_node * infix_expression_construct()
{
  infix_expression_node * object = allocate(infix_expression_node, 1);
  object->type = INFIX_EXPRESSION;
  return object;
}

enum node_type_t infix_expression_type(infix_expression_node * object)
{
  return INFIX_EXPRESSION;
}

void infix_expression_print(infix_expression_node * object)
{
  printf("(");
  node_print(object->left);
  printf("%s", object->operator);
  node_print(object->right);
  printf(")");
}

void infix_expression_destruct(infix_expression_node * object)
{
  free(object);
}