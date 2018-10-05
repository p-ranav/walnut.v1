#ifndef FUNCTION_NODE_H
#define FUNCTION_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>
#include <block_node.h>
#include <identifier_node.h>

/* function_node is an AST node type to represent a function
   declaration. Function declarations start with the keyword
   function (or the symbol λ) followed by the open paranthesis '('
   then a list of parameters (each of which is an identifier)
   and finally a closing paranthesis ')'. After this, we have
   a block_node (see block_node.h), a list of statements that
   are semi_colon delimited. For example:

   var sum = function(a, b) { return a + b; }
   var product = λ(x, y) { return x * y };

   As you can see here, functions are anonymous lambda functions
   that can be bound to variables (or stored a anonymous lambda functions
   in lists or dictionaries of even function call arguments). So,
   a function_node simply needs to store a list of parameters and a
   block_node (which internally stores a list of statements)

*/
typedef struct
{
  enum node_type_t type;    /* type = FUNCTION */
  list_t * parameters;      /* parameters = list of identifiers */
  block_node * body;
} function_node;

/* Construct a function_node and set its type to FUNCTION
   Initialize parameters list with list_new() and set body to NULL */
function_node * function_construct();

/* Overriding method that returns the FUNCTION node_type value */
enum node_type_t function_type(function_node * object);

/* Overriding method that prints a function (...) { ... } */
void function_print(function_node * object);

/* Clean up function_node - free each statement in block_node and each
   parameter in parameters list */
void function_destruct(function_node * object);

#endif