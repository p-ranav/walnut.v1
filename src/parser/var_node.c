#include <var_node.h>
#include <stdio.h>
#include <stdlib.h>

var_node * var_node_construct()
{
  var_node * object = allocate(var_node, 1);
  object->name = NULL;
  object->expression = NULL;
  object->type = VAR_STATEMENT;
  return object;
}

enum node_type_t var_node_type(var_node * object)
{
  return VAR_STATEMENT;
}

void var_node_print(var_node * object)
{
  printf("var ");
  identifier_print(object->name);
  printf(" = ");
  node_print(object->expression);
}

void var_node_destruct(var_node * object)
{

}