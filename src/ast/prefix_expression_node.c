#include <prefix_expression_node.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const char *const token_values[]; /* used in print */

prefix_expression_node *prefix_expression_construct(token operator)
{
  /* declarations */
  int operator_length;
  prefix_expression_node *object;

  object = allocate(prefix_expression_node, 1);
  object->type = PREFIX_EXPRESSION;
  object->operator = operator;

  return object;
}

enum node_type_t prefix_expression_type(prefix_expression_node *object)
{
  return object->type;
}

void prefix_expression_print(prefix_expression_node *object)
{
  printf("(");
  printf("%s", token_values[object->operator]);
  node_print(object->right);
  printf(")");
}

void prefix_expression_destruct(prefix_expression_node *object)
{
  /* free up expression to the right of the operator */
  node_destruct(object->right);

  /* lastly, free up prefix_expression_node pointer */
  free(object);
}