#ifndef PREFIX_EXPRESSION_NODE_H
#define PREFIX_EXPRESSION_NODE_H
#include <node_type.h>
#include <token.h>
#include <node.h>
#include <macros.h>

/* prefix_expression_node is an AST node type to represent an prefix expression.
   Prefix expressions are expressions of the form:
   <operator> <right_expression>

   Examples:
   var b = -a;
   if (!c) { return false; }
*/
typedef struct
{
  enum node_type_t type; /* type = PREFIX_EXPRESSION */
  token operator;        /* prefix operator. Either '-' or '!' */
  node *right;           /* expression to the right of the prefix operator */
} prefix_expression_node;

/* Construct prefix expression node. Initialize right expression and save operator */
prefix_expression_node *prefix_expression_construct(token operator);

/* return prefix expression node type 'PREFIX_EXPRESSION' */
enum node_type_t prefix_expression_type(prefix_expression_node *object);

/* print prefix expression <operator> <right_expression> */
void prefix_expression_print(prefix_expression_node *object);

/* clean up prefix expression node. Free up the right expression */
void prefix_expression_destruct(prefix_expression_node *object);

#endif