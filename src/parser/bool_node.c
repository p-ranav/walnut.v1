#include <bool_node.h>
#include <stdio.h>
#include <stdlib.h>

bool_node * bool_construct(int value)
{
  bool_node * object = allocate(bool_node, 1);
  object->type = BOOLEAN;
  object->value = value;
  return object;
}

enum node_type_t bool_type(bool_node * object)
{
  return object->type;
}

void bool_print(bool_node * object)
{
  if (object->value)
    printf("true");
  else
    printf("false");
}

void bool_destruct(bool_node * object)
{
  free(object);
}