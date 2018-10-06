#include <call_node.h>
#include <stdio.h>
#include <stdlib.h>

call_node * call_construct()
{
  /* declarations */
  call_node * object;

  object = allocate(call_node, 1);
  object->type = CALL_EXPRESSION;
  object->arguments = list_new();
  object->function = NULL;
  return object;
}

enum node_type_t call_type(call_node * object)
{
  return object->type;
}

void call_print(call_node * object)
{
  /* declarations */
  list_node_t * argument;
  list_iterator_t *it;
  node * argument_node;

  if (object->function)
    node_print(object->function);
  printf(" (");
  
  /* use list_iterator to iterate over list of tokens */
  it = list_iterator_new(object->arguments, LIST_HEAD);
  while ((argument = list_iterator_next(it)))
  {
    /* get pointer to token and print token type and value */
    argument_node = ((node *)argument->val);

    /* print statements */
    node_print(argument_node);

    if (argument->next)
      printf(", ");
  }
  deallocate(it);

  printf(")");
}

void call_destruct(call_node * object)
{
  /* declarations */
  list_node_t * argument;
  list_iterator_t * it;

  /* use list_iterator to iterate over list of tokens */
  it = list_iterator_new(object->arguments, LIST_HEAD);
  while ((argument = list_iterator_next(it)))
  {
    /* get pointer to token and free */
    node * argument_node = ((node *)argument->val);

    /* free function parameters */
    node_destruct(argument_node);
  }
  deallocate(it);

  /* free function node (identifier or expression) */
  node_destruct(object->function);

  /* clean up arguments list */
  list_destroy(object->arguments);

  /* free call_node pointer */
  free(object);
}
