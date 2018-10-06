#ifndef BOOL_NODE_H
#define BOOL_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

/* bool_node is an AST node type to represent a 
   boolean value. The value property is an integer
   (because ANSI C has no bool type unless I include
   stdbool.h) that stores either 0 or 1.

   The boolean value true is represented as:
   bool_node { .type = BOOLEAN, .value = 1 }

*/
typedef struct
{
  enum node_type_t type; /* type = BOOLEAN */
  int value;             /* value = boolean value */
} bool_node;

/* Construct a boolean node.
   sets bool_node->type to BOOLEAN and 
   sets bool_node->value to value */
bool_node * bool_construct(int value);

/* Overriding method that returns the BOOLEAN node_type value */
enum node_type_t bool_type(bool_node * object);

/* Overriding method that prints "true" if bool_node->value > 0
   else, prints "false" */
void bool_print(bool_node * object);

/* Free bool_node
   This is simple because a bool_node doesn't contain pointers */
void bool_destruct(bool_node * object);

#endif