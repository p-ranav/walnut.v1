#include <prefix_expression_node.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

prefix_expression_node *prefix_expression_construct(char *operator)
{
  /* declarations */
  int operator_length;
  prefix_expression_node *object;

  object = allocate(prefix_expression_node, 1);
  object->type = PREFIX_EXPRESSION;

  /* save prefix operator */
  operator_length = strlen(operator);
  object->operator= allocate(char, operator_length + 1);
  strcpy(object->operator, operator);
  object->operator[operator_length] = '\0';

  return object;
}

enum node_type_t prefix_expression_type(prefix_expression_node *object)
{
  return object->type;
}

void prefix_expression_print(prefix_expression_node *object)
{
  printf("(");
  printf("%s", object->operator);
  node_print(object->right);
  printf(")");
}

void prefix_expression_destruct(prefix_expression_node *object)
{
  /* free up operator character array */
  free(object->operator);

  /* free up expression to the right of the operator */
  node_destruct(object->right);

  /* lastly, free up prefix_expression_node pointer */
  free(object);
}