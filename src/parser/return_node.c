#include <return_node.h>
#include <stdio.h>
#include <stdlib.h>

node_interface *RETURN_AS_NODE = &(node_interface)
{
  .type = (enum node_type_t(*)(void *)) return_node_type,
    .print = (void(*)(void*)) return_node_print,
    .destruct = (void(*)(void *)) return_node_destruct
};


return_node * return_node_construct()
{
  return_node * object = allocate(return_node, 1);
  /* TODO: Initialize object->value */
  object->type = RETURN_STATEMENT;
  return object;
}

enum node_type_t return_node_type(return_node * object)
{
  return RETURN_STATEMENT;
}

void return_node_print(return_node * object)
{

}

void return_node_destruct(return_node * object)
{

}