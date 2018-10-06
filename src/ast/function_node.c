#include <function_node.h>
#include <stdio.h>
#include <stdlib.h>

function_node * function_construct()
{
  /* declarations */
  function_node * object;

  object = allocate(function_node, 1);
  object->type = FUNCTION;
  object->parameters = list_new(); /* This might be an empty list */
  object->body = NULL; /* Lets hope this points to something eventually */
  return object;
}

enum node_type_t function_type(function_node * object)
{
  return object->type;
}

void function_print(function_node * object)
{
  /* declarations */
  list_node_t * parameter;
  list_iterator_t *it;
  identifier_node * identifier;

  printf("function (");

  /* use list_iterator to iterate over list of tokens */
  it = list_iterator_new(object->parameters, LIST_HEAD);
  while ((parameter = list_iterator_next(it)))
  {
    /* get pointer to token and print token type and value */
    identifier = ((identifier_node *)parameter->val);

    /* print statements */
    identifier_print(identifier);

    if (parameter->next)
      printf(", ");
  }
  deallocate(it);

  /* maybe the curly braces should be part of block_print? */
  printf(") { ");

  block_print(object->body);

  printf(" }");
}

void function_destruct(function_node * object)
{
  /* declarations */
  list_node_t * parameter;
  list_iterator_t * it;

  /* use list_iterator to iterate over list of tokens */
  it = list_iterator_new(object->parameters, LIST_HEAD);
  while ((parameter = list_iterator_next(it)))
  {
    /* get pointer to token and free */
    identifier_node * parameter_node = ((identifier_node *)parameter->val);

    /* free function parameters */
    identifier_destruct(parameter_node);
  }
  deallocate(it);

  /* destroy list of parameters (each of which is an identifier) */
  list_destroy(object->parameters);

  /* clean up function body */
  block_destruct(object->body);

  /* lastly, free up function_node pointer */
  free(object);
}
