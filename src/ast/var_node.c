#include <var_node.h>
#include <stdio.h>
#include <stdlib.h>

var_node *var_node_construct()
{
  /* declarations */
  var_node *object;

  object = allocate(var_node, 1);
  object->name = NULL;
  object->expression = NULL;
  object->type = VAR_STATEMENT;
  return object;
}

enum node_type_t var_node_type(var_node *object)
{
  return object->type;
}

void var_node_print(var_node *object)
{
  printf("var ");

  /* print identifier */
  identifier_print(object->name);

  printf(" = ");

  /* print expression */
  node_print(object->expression);
}

void var_node_destruct(var_node *object)
{
  /* clean up variable name */
  identifier_destruct(object->name);

  /* clean up variable value */
  node_destruct(object->expression);

  /* free up var_node pointer */
  free(object);
}