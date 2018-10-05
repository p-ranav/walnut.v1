#ifndef STRING_NODE_H
#define STRING_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

typedef struct
{
  enum node_type_t type;  /* type = STRING */
  char * value;           /* value = buffer of multi-byte characters */
} string_node;

string_node * string_construct(char * value);

enum node_type_t string_type(string_node * object);
void string_print(string_node * object);
void string_destruct(string_node * object);

#endif