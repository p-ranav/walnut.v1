#ifndef INFIX_EXPRESSION_NODE_H
#define INFIX_EXPRESSION_NODE_H
#include <node_type.h>
#include <token.h>
#include <node.h>
#include <macros.h>

/* infix_expression_node is an AST node type to represent an infix expression.
   Infix expressions are expressions of the form:
   <left_expression> <operator> <right_expression>

   Examples:
   (a + b)
   (a * (b - c))
   ((a + b) - (c + d))
*/
typedef struct
{
  enum node_type_t type; /* type = INFIX_EXPRESSION */
  node *left;            /* expression node to the left of the infix operator */
  token operator;        /* infix operator */
  node *right;           /* expression node to the right of the infix operator */
} infix_expression_node;

/* initialize left and right of infix expression. String copy the operator string */
infix_expression_node *infix_expression_construct(token operator);

/* return the type 'INFIX_EXPRESSION' */
enum node_type_t infix_expression_type(infix_expression_node *object);

/* print infix expression (<left> <operator> <right>) */
void infix_expression_print(infix_expression_node *object);

/* free up the operator character buffer, left and right expressions */
void infix_expression_destruct(infix_expression_node *object);

#endif