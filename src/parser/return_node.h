#ifndef RETURN_NODE_H
#define RETURN_NODE_H
#include <node_type.h>
#include <node.h>
#include <node_type.h>
#include <macros.h>

typedef struct
{
  enum node_type_t type;
  /* TODO: add expression node for value */
} return_node;

return_node * return_node_construct();

enum node_type_t return_node_type(return_node * object);
void return_node_print(return_node * object);
void return_node_destruct(return_node * object);

#endif