#include <infix_expression_node.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const char *const token_values[]; /* used in print */

infix_expression_node *infix_expression_construct(token operator)
{
  /* declarations */
  infix_expression_node *object;

  object = allocate(infix_expression_node, 1);
  object->type = INFIX_EXPRESSION;
  object->operator = operator;

  return object;
}

enum node_type_t infix_expression_type(infix_expression_node *object)
{
  return object->type;
}

void infix_expression_print(infix_expression_node *object)
{
  printf("(");
  node_print(object->left);
  printf(" %s ", token_values[object->operator]);
  node_print(object->right);
  printf(")");
}

void infix_expression_destruct(infix_expression_node *object)
{
  /* free up expression to the left of infix operator */
  node_destruct(object->left);

  /* free up expression to the right of infix operator */
  node_destruct(object->right);

  /* free up infix_expression_node pointer */
  free(object);
}