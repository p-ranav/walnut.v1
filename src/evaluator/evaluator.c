#include <evaluator.h>

/* Parser headers */
#include <integer_node.h>
#include <bool_node.h>
#include <prefix_expression_node.h>

/* Object model headers */
#include <integer_object.h>
#include <bool_object.h>

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
  case BOOLEAN:
    return eval_boolean(ast_node);
    break;
  case PREFIX_EXPRESSION:
    return eval_prefix_expression(ast_node);
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

object * eval_boolean(node * ast_node)
{
  /* declarations */
  boolean_object * obj;
  object_interface * BOOLEAN_AS_OBJECT;

  obj = boolean_object_construct(((bool_node *)ast_node->instance)->value);

  BOOLEAN_AS_OBJECT = allocate(object_interface, 1);
  BOOLEAN_AS_OBJECT->type = (enum object_type_t(*)(void *))boolean_object_type;
  BOOLEAN_AS_OBJECT->inspect = (const char *(*)(void *))boolean_object_inspect;
  BOOLEAN_AS_OBJECT->destruct = (void(*)(void *))boolean_object_destruct;
  return object_construct(obj, BOOLEAN_AS_OBJECT);
}

object * eval_prefix_expression(node * ast_node)
{
  /* declarations */
  object * right;
  char * operator;

  right = eval(((prefix_expression_node *)ast_node->instance)->right);
  operator = ((prefix_expression_node *)ast_node->instance)->operator;
  
  if (strcmp(operator, "!") == 0)
  {
    return eval_bang_operator(right);
  }
  else if (strcmp(operator, "-") == 0)
  {
    return eval_unary_minus_operator(right);
  }
  else
  {
    return NULL;
  }
}

object * eval_bang_operator(object * right)
{
  /* declarations */
  boolean_object * obj;
  object_interface * BOOLEAN_AS_OBJECT;

  obj = boolean_object_construct(0); /* initialize as FALSE */

  BOOLEAN_AS_OBJECT = allocate(object_interface, 1);
  BOOLEAN_AS_OBJECT->type = (enum object_type_t(*)(void *))boolean_object_type;
  BOOLEAN_AS_OBJECT->inspect = (const char *(*)(void *))boolean_object_inspect;
  BOOLEAN_AS_OBJECT->destruct = (void(*)(void *))boolean_object_destruct;

  /* return TRUE if right is NULL */
  if (object_type(right) == OBJECT_NULL) {
    obj->value = 1;
  }

  /* return TRUE if right is FALSE */
  else if (((boolean_object *)right->instance)->value == 0)
  {
    obj->value = 1;
  }

  return object_construct(obj, BOOLEAN_AS_OBJECT);
}

object * eval_unary_minus_operator(object * right)
{
  /* TODO: support INTEGER, FLOAT and DOUBLE types */
  if (object_type(right) == OBJECT_INTEGER)
  {
    return eval_negate_integer(right);
  }
  else
  {
    return NULL;
  }
}

object * eval_negate_integer(object * right)
{
  /* TODO: delete right before returning result? */

  /* declarations */
  integer_object * obj;
  object_interface * INTEGER_AS_OBJECT;

  obj = integer_object_construct(-1 * ((integer_object *)right->instance)->value);

  INTEGER_AS_OBJECT = allocate(object_interface, 1);
  INTEGER_AS_OBJECT->type = (enum object_type_t(*)(void *))integer_object_type;
  INTEGER_AS_OBJECT->inspect = (const char *(*)(void *))integer_object_inspect;
  INTEGER_AS_OBJECT->destruct = (void(*)(void *))integer_object_destruct;

  return object_construct(obj, INTEGER_AS_OBJECT);
}