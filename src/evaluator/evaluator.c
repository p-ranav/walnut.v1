#include <evaluator.h>

/* Parser headers */
#include <integer_node.h>

/* Object model headers */
#include <integer_object.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

object * eval(node * ast_node)
{
  switch (node_type(ast_node))
  {
  case INTEGER:
    return eval_integer(ast_node);
    break;
  default:
    return NULL;
    break;
  }
}

object * eval_integer(node * ast_node)
{
  /* declarations */
  integer_object * obj;
  object_interface * INTEGER_AS_OBJECT;

  obj = integer_object_construct(((integer_node *)ast_node->instance)->value);

  INTEGER_AS_OBJECT = allocate(object_interface, 1);
  INTEGER_AS_OBJECT->type = (enum object_type_t(*)(void *))integer_object_type;
  INTEGER_AS_OBJECT->inspect = (const char *(*)(void *))integer_object_inspect;
  INTEGER_AS_OBJECT->destruct = (void(*)(void *))integer_object_destruct;
  return object_construct(obj, INTEGER_AS_OBJECT);
}