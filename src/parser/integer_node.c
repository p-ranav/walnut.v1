#include <integer_node.h>
#include <stdio.h>
#include <stdlib.h>

integer_node * integer_construct(int value)
{
  integer_node * object = allocate(integer_node, 1);
  object->type = INTEGER;
  object->value = value;
  return object;
}

enum node_type_t integer_type(integer_node * object)
{
  return object->type;
}

void integer_print(integer_node * object)
{
  printf("%d", object->value);
}

void integer_destruct(integer_node * object)
{
  free(object);
}