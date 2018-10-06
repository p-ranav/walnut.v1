#ifndef BLOCK_NODE_H
#define BLOCK_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>
#include <list.h>

/* block_node is an AST node type to represent a block of code
   By 'block of code', I mean a list of statements
   within curly braces {...}. For example:

   {
      var x = 2;
      print(x);
   }

   The above code is a block_node with 2 statements:
   a variable declaration and a function call.

*/
typedef struct
{
  enum node_type_t type; /* type = BLOCK */
  list_t *statements;    /* list of statements in block of code {...} */
} block_node;

/* Construct a block node.
   Makes sure that block_node->statements is not NULL by calling list_new() */
block_node *block_construct();

/* Overriding method that returns the BLOCK node_type value */
enum node_type_t block_type(block_node *object);

/* Overriding method that prints all statements in a block_node */
void block_print(block_node *object);

/* Clean up block node - Free each statement in block_node->statements */
void block_destruct(block_node *object);

#endif