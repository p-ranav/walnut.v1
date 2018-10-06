#include <if_expression_node.h>
#include <stdio.h>
#include <stdlib.h>

if_expression_node *if_expression_construct()
{
  /* declarations */
  if_expression_node *object;

  object = allocate(if_expression_node, 1);
  object->type = IF_EXPRESSION;
  object->condition = NULL;   /* lets hope this points to an expression */
  object->consequence = NULL; /* lets hope this points to a block node eventually */
  object->alternative = NULL; /* this can be NULL. If there's an else block, this should point to it */
  return object;
}

enum node_type_t if_expression_type(if_expression_node *object)
{
  return object->type;
}

void if_expression_print(if_expression_node *object)
{
  printf("if ");
  node_print(object->condition);

  /* maybe the curly braces should be part of block_print? */
  printf(" { ");
  block_print(object->consequence);
  if (object->alternative)
  {
    printf(" } else { ");
    block_print(object->alternative);
  }
  printf(" }");
}

void if_expression_destruct(if_expression_node *object)
{
  /* free up condition expression */
  node_destruct(object->condition);

  /* clean up if consequence block_node */
  block_destruct(object->consequence);

  /* if an alternative is provided, i.e., the else block, then free it up */
  if (object->alternative)
    block_destruct(object->alternative);

  /* lastly, free up the if_expression_node pointer */
  free(object);
}