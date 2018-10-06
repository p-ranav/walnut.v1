#ifndef INTEGER_NODE_H
#define INTEGER_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

/* integer_node is an AST node type that represents a 32-bit integer
   This is the default integer type for type inference.

   For example:
   var a = 15;  // Here, '15' is saved as an int

*/
typedef struct
{
  enum node_type_t type;    /* type = INTEGER */
  int value;                /* value = int32 value */
} integer_node;

/* construct an integer_node and assign node->value to input value */
integer_node * integer_construct(int value);

/* returns the type 'INTEGER' */
enum node_type_t integer_type(integer_node * object);

/* prints the integer value with printf */
void integer_print(integer_node * object);

/* Simply free integer_node object pointer */
void integer_destruct(integer_node * object);

#endif