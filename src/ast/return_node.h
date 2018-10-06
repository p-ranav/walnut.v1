#ifndef RETURN_NODE_H
#define RETURN_NODE_H
#include <node_type.h>
#include <node.h>
#include <node_type.h>
#include <macros.h>

/* return_node is an AST node type to represent return statements.
   Return statements return an expression. The return expression
   could be a complex expression, e.g., return (a + (b - c) * (d /e));
   or it could be a simple expression, e.g., return 0;
*/
typedef struct
{
  enum node_type_t type; /* type = RETURN_STATEMENT */
  node *expression;      /* expression being returned */
} return_node;

/* Construct return node - initialize return expression */
return_node *return_node_construct();

/* return the 'RETURN' node type */
enum node_type_t return_node_type(return_node *object);

/* print the return expression */
void return_node_print(return_node *object);

/* call node_destruct on the return expression and free return expression node */
void return_node_destruct(return_node *object);

#endif