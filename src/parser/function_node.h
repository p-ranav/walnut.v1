#ifndef FUNCTION_NODE_H
#define FUNCTION_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>
#include <block_node.h>
#include <identifier_node.h>

typedef struct
{
  enum node_type_t type;    /* type = FUNCTION */
  list_t * parameters;      /* parameters = list of identifiers */
  block_node * body;
} function_node;

function_node * function_construct();

enum node_type_t function_type(function_node * object);
void function_print(function_node * object);
void function_destruct(function_node * object);

#endif