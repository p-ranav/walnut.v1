#include <infix_expression_node.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

infix_expression_node * infix_expression_construct(char * operator)
{
  /* declarations */
  int operator_length;
  infix_expression_node * object;

  object = allocate(infix_expression_node, 1);
  object->type = INFIX_EXPRESSION;

  /* save prefix operator */
  operator_length = strlen(operator);
  object->operator = allocate(char, operator_length + 1);
  strcpy(object->operator, operator);
  object->operator[operator_length] = '\0';

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
  free(object->operator);
  node_destruct(object->left);
  node_destruct(object->right);
  free(object);
}