#ifndef IF_EXPRESSION_NODE_H
#define IF_EXPRESSION_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>
#include <block_node.h>

/* if_expression_node is an AST node that represents an if-else
   block. There is no else-if support as of right now. So, this
   AST node represents code that looks like this:

   [...]
   if (a % 2 == 0) { return true; } else { return false; }
   [...]

   The if expression starts with the keyword 'if', followed
   by a condition expression. After the condition, we have the
   consequence block of code and optionally an alternative block
   of code that is executed when the condition is false.

*/
typedef struct
{
  enum node_type_t type;       /* type = IF_EXPRESSION */
  node * condition;            /* condition expression */
  block_node * consequence;    /* block of code following the if expression */
  block_node * alternative;    /* block of code following the else expression. Could be NULL */
} if_expression_node;

/* Construct an if expression - initialize condition, consequence and alternative nodes */
if_expression_node * if_expression_construct();

/* return IF_EXPRESSION node type */
enum node_type_t if_expression_type(if_expression_node * object);

/* print an if expression, e.g., if (...) { ... } else { ... } */
void if_expression_print(if_expression_node * object);

/* free an if expression node - clean up block nodes and condition expression */
void if_expression_destruct(if_expression_node * object);

#endif