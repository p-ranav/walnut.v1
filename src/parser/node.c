#include <node.h>
#include <macros.h>

#include <stdlib.h>

node * node_construct(void * instance, node_interface * interface)
{
  node * ast_node = allocate(node, 1);
  ast_node->instance = instance;
  ast_node->interface = interface;
  return ast_node;
}

enum node_type_t node_type(node * object)
{
  return (object->interface->type)(object->instance);
}

void node_print(node * object)
{
  (object->interface->print)(object->instance);
}

void node_destruct(node * object)
{
  (object->interface->destruct)(object->instance);
  free(object);
}