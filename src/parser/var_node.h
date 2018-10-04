#ifndef VAR_NODE_H
#define VAR_NODE_H
#include <node_type.h>
#include <node.h>
#include <identifier_node.h>
#include <node_type.h>
#include <macros.h>

typedef struct
{
  enum node_type_t type;
  identifier_node * name;
  /* TODO: add expression node for value */
} var_node;

var_node * var_node_construct();

enum node_type_t var_node_type(var_node * object);
void var_node_print(var_node * object);
void var_node_destruct(var_node * object);

#endif