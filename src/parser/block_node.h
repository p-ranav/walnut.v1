#ifndef BLOCK_NODE_H
#define BLOCK_NODE_H
#include <node_type.h>
#include <node.h>
#include <macros.h>
#include <list.h>

typedef struct
{
  enum node_type_t type;    /* type = BLOCK */
  list_t * statements;      /* list of statements in block of code {...} */
} block_node;

block_node * block_construct();

enum node_type_t block_type(block_node * object);
void block_print(block_node * object);
void block_destruct(block_node * object);

#endif