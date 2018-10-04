#ifndef BOOL_NODE_H
#define BOOL_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

typedef struct
{
  enum node_type_t type; /* type = BOOLEAN */
  int value;             /* value = boolean value */
} bool_node;

bool_node * bool_construct(int value);

enum node_type_t bool_type(bool_node * object);
void bool_print(bool_node * object);
void bool_destruct(bool_node * object);

#endif