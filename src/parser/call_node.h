#ifndef CALL_NODE_H
#define CALL_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>
#include <block_node.h>
#include <identifier_node.h>
#include <function_node.h>

typedef struct
{
  enum node_type_t type;    /* type = FUNCTION */
  node * function;          /* identifier or function literal */
  list_t * arguments;       /* list of arguments */
} call_node;

call_node * call_construct();

enum node_type_t call_type(call_node * object);
void call_print(call_node * object);
void call_destruct(call_node * object);

#endif