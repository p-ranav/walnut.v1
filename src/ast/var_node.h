#ifndef VAR_NODE_H
#define VAR_NODE_H
#include <node_type.h>
#include <node.h>
#include <identifier_node.h>
#include <node_type.h>
#include <macros.h>

/* var_node is an AST node type that represents a variable declaration.
   A variable declaration starts with the keyword 'var' followed by 
   an identifier. Then, we expect to see an equals sign '=' followed
   by an expression. For example:

   var x = 5;
   var y = get_string_at(5);
   var z = 3.14f;
   var a = 5.0;
   var b = true;
   var c = "Hello";
   var d = (a - x);
   var e = function(x, y) { return x + y; }

   All of the above are valid variable declarations. The variable name
   is an identifier and its value is an expression (to be evaluated later).

*/
typedef struct
{
  enum node_type_t type;        /* type = VAR_STATEMENT */
  identifier_node * name;       /* name (identifier) of the variable*/
  node * expression;            /* expression to the right of the '=' sign */
} var_node;

/* construct a variable node - initialize identifier name and expression */
var_node * var_node_construct();

/* return 'VAR_STATEMENT' node type */
enum node_type_t var_node_type(var_node * object);

/* print variable declaration - var <name> = <expression> */
void var_node_print(var_node * object);

/* clean up variable declration
   identifier_destruct(name) and node_destruct(expression) */
void var_node_destruct(var_node * object);

#endif