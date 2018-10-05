#include <double_node.h>
#include <stdio.h>
#include <stdlib.h>

double_node * double_construct(double value)
{
  double_node * object = allocate(double_node, 1);
  object->type = DOUBLE;
  object->value = value;
  return object;
}

enum node_type_t double_type(double_node * object)
{
  return object->type;
}

void double_print(double_node * object)
{
  printf("%f", object->value);
}

void double_destruct(double_node * object)
{
  free(object);
}