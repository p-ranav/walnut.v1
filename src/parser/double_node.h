#ifndef DOUBLE_NODE_H
#define DOUBLE_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

typedef struct
{
  enum node_type_t type;  /* type = DOUBLE */
  double value;           /* value = double value */
} double_node;

double_node * double_construct(double value);

enum node_type_t double_type(double_node * object);
void double_print(double_node * object);
void double_destruct(double_node * object);

#endif