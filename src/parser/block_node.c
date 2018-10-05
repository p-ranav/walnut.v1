#include <block_node.h>
#include <stdio.h>
#include <stdlib.h>

block_node * block_construct()
{
  block_node * object = allocate(block_node, 1);
  object->type = BLOCK;
  object->statements = list_new();
  return object;
}

enum node_type_t block_type(block_node * object)
{
  return object->type;
}

void block_print(block_node * object)
{
  /* use list_iterator to iterate over list of tokens */
  list_node_t * statement;
  list_iterator_t *it = list_iterator_new(object->statements, LIST_HEAD);
  while ((statement = list_iterator_next(it)))
  {
    /* get pointer to token and print token type and value */
    node * statement_node = ((node *)statement->val);

    /* print statements */
    node_print(statement_node);
  }
  deallocate(it);
}

void block_destruct(block_node * object)
{
  free(object);
}