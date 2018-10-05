#include <infix_expression_node.h>
#include <stdio.h>
#include <stdlib.h>

infix_expression_node * infix_expression_construct()
{
  infix_expression_node * object = allocate(infix_expression_node, 1);
  object->type = INFIX_EXPRESSION;
  return object;
}

enum node_type_t infix_expression_type(infix_expression_node * object)
{
  return object->type;
}

void infix_expression_print(infix_expression_node * object)
{
  printf("(");
  node_print(object->left);
  printf(" %s ", object->operator);
  node_print(object->right);
  printf(")");
}

void infix_expression_destruct(infix_expression_node * object)
{
  node_destruct(object->left);
  node_destruct(object->right);
  free(object);
}