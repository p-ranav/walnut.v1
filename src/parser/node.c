#include <node.h>
#include <macros.h>

#include <stdlib.h>

struct node_t * node_construct(void * instance, node_interface * interface)
{
  struct node_t * node = allocate(struct node_t, 1);
  node->instance = instance;
  node->interface = interface;
  return node;
}

enum node_type_t node_type(struct node_t * node)
{
  return (node->interface->type)(node->instance);
}

void node_print(struct node_t * node)
{
  (node->interface->print)(node->instance);
}

void node_destruct(struct node_t * node)
{
  (node->interface->destruct)(node->instance);
  free(node);
}