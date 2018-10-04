#ifndef INTEGER_NODE_H
#define INTEGER_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

typedef struct
{
  enum node_type_t type; /* type = INTEGER */
  int value;           /* value = int32 value */
} integer_node;

integer_node * integer_construct(int value);

enum node_type_t integer_type(integer_node * object);
void integer_print(integer_node * object);
void integer_destruct(integer_node * object);

#endif