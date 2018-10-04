#include <if_expression_node.h>
#include <stdio.h>
#include <stdlib.h>

if_expression_node * if_expression_construct()
{
  if_expression_node * object = allocate(if_expression_node, 1);
  object->type = IF_EXPRESSION;
  object->condition = NULL;
  object->consequence = NULL;
  object->alternative = NULL;
  return object;
}

enum node_type_t if_expression_type(if_expression_node * object)
{
  return IF_EXPRESSION;
}

void if_expression_print(if_expression_node * object)
{
  printf("if ");
  node_print(object->condition);
  printf(" { ");
  block_print(object->consequence);
  if (object->alternative)
  {
    printf(" } else { ");
    block_print(object->alternative);
  }
  printf(" }");
}

void if_expression_destruct(if_expression_node * object)
{
  free(object);
}