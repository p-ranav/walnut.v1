#include <bool_node.h>
#include <stdio.h>
#include <stdlib.h>

bool_node *bool_construct(int value)
{
  /* declarations */
  bool_node *object;

  object = allocate(bool_node, 1);
  object->type = BOOLEAN;
  object->value = value;
  return object;
}

enum node_type_t bool_type(bool_node *object)
{
  return object->type;
}

void bool_print(bool_node *object)
{
  /* Print "true" if value > 0, "false" otherwise */
  if (object->value)
    printf("true");
  else
    printf("false");
}

void bool_destruct(bool_node *object)
{
  /* simply free bool_node pointer */
  free(object);
}