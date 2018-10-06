#ifndef CALL_NODE_H
#define CALL_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>
#include <block_node.h>
#include <identifier_node.h>
#include <function_node.h>

/* call_node is an AST node type to represent function calls.
   Function calls can look one of two ways:

   (1) print("Hello World")
       This is a simple call where the function name is an
       identifier. After this identifier, we have the '('
       paranthesis and a list of arguments, until we reach
       ')'

   (2) function(a, b) { return a * b }(5, 10)
       This is a lambda function - defined and then
       immediately called with arguments. Here, we parse a
       function and then subsequently the list of arguments
       to pass to this function. 
*/
typedef struct
{
  enum node_type_t type; /* type = CALL */
  node *function;        /* identifier or function literal */
  list_t *arguments;     /* list of arguments */
} call_node;

/* construct a call_node. Initialize call->arguments (list_new())
   and set call->function to NULL to be assigned later in the parser */
call_node *call_construct();

/* Overriding method that returns the CALL node_type value */
enum node_type_t call_type(call_node *object);

/* Overriding method that prints the name and arguments in the function call */
void call_print(call_node *object);

/* Cleans up call_node struct
   Free list of arguments and the function node pointer */
void call_destruct(call_node *object);

#endif