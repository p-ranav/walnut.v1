#ifndef DOUBLE_NODE_H
#define DOUBLE_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

/* double_node is an AST node type to represent
   a double-precision floating point number. So,
   the value is a double type.
*/
typedef struct
{
  enum node_type_t type; /* type = DOUBLE */
  double value;          /* value = double value */
} double_node;

/* Construct a double_node and set its type to DOUBLE */
double_node *double_construct(double value);

/* Overriding method that returns the DOUBLE node_type value */
enum node_type_t double_type(double_node *object);

/* Overriding method that prints the value of the double with printf */
void double_print(double_node *object);

/* Free double_node pointer - simple since it has no contained pointers */
void double_destruct(double_node *object);

#endif