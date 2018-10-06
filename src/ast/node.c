#include <node.h>
#include <macros.h>

#include <stdlib.h>

node *node_construct(void *instance, node_interface *interface)
{
  /* declarations */
  node *ast_node;

  ast_node = allocate(node, 1);
  ast_node->instance = instance;
  ast_node->interface = interface;
  return ast_node;
}

enum node_type_t node_type(node *object)
{
  /* call the *_type(...) of the derived type */
  return (object->interface->type)(object->instance);
}

void node_print(node *object)
{
  /* call the *_print(...) of the derived type */
  (object->interface->print)(object->instance);
}

void node_destruct(node *object)
{
  /* call the *_destruct(...) of the derived type */
  (object->interface->destruct)(object->instance);

  /* free up the interface table */
  free(object->interface);

  /* finally, free up node pointer */
  free(object);
}