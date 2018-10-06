#ifndef FLOAT_NODE_H
#define FLOAT_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

/* float_node is an AST node type to represent
   a single-precision floating point number. So,
   the value is a float type.
*/
typedef struct
{
  enum node_type_t type; /* type = FLOAT */
  float value;           /* value = float32 value */
} float_node;

/* Construct a float_node and set its type to FLOAT */
float_node * float_construct(float value);

/* Overriding method that returns the FLOAT node_type value */
enum node_type_t float_type(float_node * object);

/* Overriding method that prints the value of the float with printf */
void float_print(float_node * object);

/* Free float_node pointer - simple since it has no contained pointers */
void float_destruct(float_node * object);

#endif