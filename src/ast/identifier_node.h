#ifndef IDENTIFIER_NODE_H
#define IDENTIFIER_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

/* identifier_node is an AST node type to represent an identifier.
   Since this language fully supports unicode (UTF-8 encoding), just
   about any sequence of unicode characters (that isn't already a keyword
   symbol like 'λ') is cool as an identifier. For example:

   var a = 5;              // a is the identifier here
   var 信息_01 = "secret"; // 信息_01 is the identifier here
   
*/
typedef struct
{
  enum node_type_t type; /* type = IDENTIFIER */
  char *value;           /* value = array of multi-byte characters */
} identifier_node;

/* String copy the input sequence of multi-byte characters and construct
   an identifier node */
identifier_node *identifier_construct(char *name);

/* Returns 'IDENTIFIER' node_type assuming object was constructed correctly */
enum node_type_t identifier_type(identifier_node *object);

/* Print the identifier name, e.g., a or 信息_01 */
void identifier_print(identifier_node *object);

/* Clean up identifier name - free object->value */
void identifier_destruct(identifier_node *object);

#endif