#ifndef FLOAT_NODE_H
#define FLOAT_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

typedef struct
{
  enum node_type_t type; /* type = FLOAT */
  float value;           /* value = float32 value */
} float_node;

float_node * float_construct(float value);

enum node_type_t float_type(float_node * object);
void float_print(float_node * object);
void float_destruct(float_node * object);

#endif