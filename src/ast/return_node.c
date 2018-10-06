#include <return_node.h>
#include <stdio.h>
#include <stdlib.h>

return_node * return_node_construct()
{
  return_node * object = allocate(return_node, 1);
  object->expression = NULL;
  object->type = RETURN_STATEMENT;
  return object;
}

enum node_type_t return_node_type(return_node * object)
{
  return object->type;
}

void return_node_print(return_node * object)
{
  printf("return ");
  node_print(object->expression);
}

void return_node_destruct(return_node * object)
{
  node_destruct(object->expression);
  free(object);
}