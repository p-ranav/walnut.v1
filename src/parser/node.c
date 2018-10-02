#include <node.h>
#include <macros.h>

#include <stdlib.h>

node * node_construct(void * instance, node_interface * interface)
{
  node * object = allocate(node, 1);
  object->instance = instance;
  object->interface = interface;
  return object;
}
