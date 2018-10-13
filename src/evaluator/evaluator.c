#include <evaluator.h>

/* Parser headers */
#include <integer_node.h>
#include <bool_node.h>
#include <prefix_expression_node.h>
#include <infix_expression_node.h>

/* Object model headers */
#include <integer_object.h>
#include <bool_object.h>
#include <null_object.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

object * eval(node * ast_node)
{
  /* declarations */
  object * result;

  switch (node_type(ast_node))
  {
  case INTEGER:
    result = eval_integer(ast_node);
    break;
  case BOOLEAN:
    result = eval_boolean(ast_node);
    break;
  case PREFIX_EXPRESSION:
    result = eval_prefix_expression(ast_node);
    break;
  case INFIX_EXPRESSION:
    result = eval_infix_expression(ast_node);
    break;
  default:
    result = eval_null();
    break;
  }

  return result;
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

object * eval_null()
{
  /* declarations */
  null_object * obj;
  object_interface * NULL_AS_OBJECT;

  obj = null_object_construct();

  NULL_AS_OBJECT = allocate(object_interface, 1);
  NULL_AS_OBJECT->type = (enum object_type_t(*)(void *))null_object_type;
  NULL_AS_OBJECT->inspect = (const char *(*)(void *))null_object_inspect;
  NULL_AS_OBJECT->destruct = (void(*)(void *))null_object_destruct;
  return object_construct(obj, NULL_AS_OBJECT);
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
    return eval_null();
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
    return eval_null();
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

object * eval_infix_expression(node * ast_node)
{
  /* declarations */
  object * left;
  object * right;
  char * operator;

  left = eval(((infix_expression_node *)ast_node->instance)->left);
  right = eval(((infix_expression_node *)ast_node->instance)->right);
  operator = ((infix_expression_node *)ast_node->instance)->operator;

  if (object_type(left) == OBJECT_INTEGER && object_type(right) == OBJECT_INTEGER)
  {
    /* integer infix expression, operators '+', '-', '*', '/' and '%' */
    return eval_integer_infix_expression(operator, left, right);
  }
  else if (object_type(left) == OBJECT_BOOLEAN && object_type(right) == OBJECT_BOOLEAN)
  {
    /* boolean infix expression, operators '==' and '!=' */
    return eval_boolean_infix_expression(operator, left, right);
  }
  else
  {
    return eval_null();
  }
}

object * eval_integer_infix_expression(char * operator, object * left, object * right)
{
  /* declarations */
  int result;
  int left_value;
  int right_value;
  integer_object * obj;
  boolean_object * bool_obj;
  object_interface * INTEGER_AS_OBJECT;
  object_interface * BOOLEAN_AS_OBJECT;

  /* initializations */
  result = 0;
  left_value = ((integer_object *)left->instance)->value;
  right_value = ((integer_object *)right->instance)->value;

  /* integer as object */
  INTEGER_AS_OBJECT = allocate(object_interface, 1);
  INTEGER_AS_OBJECT->type = (enum object_type_t(*)(void *))integer_object_type;
  INTEGER_AS_OBJECT->inspect = (const char *(*)(void *))integer_object_inspect;
  INTEGER_AS_OBJECT->destruct = (void(*)(void *))integer_object_destruct;
  
  /* boolean as object */
  BOOLEAN_AS_OBJECT = allocate(object_interface, 1);
  BOOLEAN_AS_OBJECT->type = (enum object_type_t(*)(void *))boolean_object_type;
  BOOLEAN_AS_OBJECT->inspect = (const char *(*)(void *))boolean_object_inspect;
  BOOLEAN_AS_OBJECT->destruct = (void(*)(void *))boolean_object_destruct;
  
  if (strcmp(operator, "+") == 0)
  {
    result = left_value + right_value;
    obj = integer_object_construct(result);
    return object_construct(obj, INTEGER_AS_OBJECT);
  }
  else if (strcmp(operator, "-") == 0)
  {
    result = left_value - right_value;
    obj = integer_object_construct(result);
    return object_construct(obj, INTEGER_AS_OBJECT);
  }
  else if (strcmp(operator, "*") == 0)
  {
    result = left_value * right_value;
    obj = integer_object_construct(result);
    return object_construct(obj, INTEGER_AS_OBJECT);
  }
  else if (strcmp(operator, "/") == 0)
  {
    result = left_value / right_value;
    obj = integer_object_construct(result);
    return object_construct(obj, INTEGER_AS_OBJECT);
  }
  else if (strcmp(operator, "%") == 0)
  {
    result = left_value % right_value;
    obj = integer_object_construct(result);
    return object_construct(obj, INTEGER_AS_OBJECT);
  }
  else if (strcmp(operator, ">") == 0)
  {
    result = (left_value > right_value);
    bool_obj = boolean_object_construct(result);
    return object_construct(bool_obj, BOOLEAN_AS_OBJECT);
  }
  else if (strcmp(operator, ">=") == 0)
  {
    result = (left_value >= right_value);
    bool_obj = boolean_object_construct(result);
    return object_construct(bool_obj, BOOLEAN_AS_OBJECT);
  }
  else if (strcmp(operator, "<") == 0)
  {
    result = (left_value < right_value);
    bool_obj = boolean_object_construct(result);
    return object_construct(bool_obj, BOOLEAN_AS_OBJECT);
  }
  else if (strcmp(operator, "<=") == 0)
  {
    result = (left_value > right_value);
    bool_obj = boolean_object_construct(result);
    return object_construct(bool_obj, BOOLEAN_AS_OBJECT);
  }
  else if (strcmp(operator, "==") == 0)
  {
    result = (left_value == right_value);
    bool_obj = boolean_object_construct(result);
    return object_construct(bool_obj, BOOLEAN_AS_OBJECT);
  }
  else if (strcmp(operator, "!=") == 0)
  {
    result = (left_value != right_value);
    bool_obj = boolean_object_construct(result);
    return object_construct(bool_obj, BOOLEAN_AS_OBJECT);
  }
  else
  {
    return eval_null();
  }

}

object * eval_boolean_infix_expression(char * operator, object * left, object * right)
{
  /* declarations */
  int result;
  int left_value;
  int right_value;
  boolean_object * obj;
  object_interface * BOOLEAN_AS_OBJECT;

  /* initializations */
  result = 0;
  left_value = ((boolean_object *)left->instance)->value;
  right_value = ((boolean_object *)right->instance)->value;

  if (strcmp(operator, "==") == 0)
  {
    result = (left_value == right_value);
  }
  else if (strcmp(operator, "!=") == 0)
  {
    result = (left_value != right_value);
  }
  else
  {
    return eval_null();
  }

  obj = boolean_object_construct(result);

  BOOLEAN_AS_OBJECT = allocate(object_interface, 1);
  BOOLEAN_AS_OBJECT->type = (enum object_type_t(*)(void *))boolean_object_type;
  BOOLEAN_AS_OBJECT->inspect = (const char *(*)(void *))boolean_object_inspect;
  BOOLEAN_AS_OBJECT->destruct = (void(*)(void *))boolean_object_destruct;
  return object_construct(obj, BOOLEAN_AS_OBJECT);
}