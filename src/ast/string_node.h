#ifndef STRING_NODE_H
#define STRING_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

/* string_node is an AST node type to represent a string literal
   This language supports unicode and so this string literal include
   multi-byte UTF-8 encoded characters
*/
typedef struct
{
  enum node_type_t type;  /* type = STRING */
  char * value;           /* value = buffer of multi-byte characters */
} string_node;

/* string copy input argument value */
string_node * string_construct(char * value);

/* return 'STRING' node type */
enum node_type_t string_type(string_node * object);

/* print string value with double quotes */
void string_print(string_node * object);

/* clean up string->value char array */
void string_destruct(string_node * object);

#endif