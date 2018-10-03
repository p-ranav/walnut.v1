#ifndef IDENTIFIER_NODE_H
#define IDENTIFIER_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
  enum node_type type; /* type = IDENTIFIER */
  char * value;        /* name = array of multi-byte characters */
} identifier_node;

identifier_node * identifier_construct(char * name);

enum node_type_t identifier_type(identifier_node * object);
void identifier_print(identifier_node * object);
void identifier_destruct(identifier_node * object);

#endif