#include <float_node.h>
#include <stdio.h>
#include <stdlib.h>

float_node * float_construct(float value)
{
  float_node * object = allocate(float_node, 1);
  object->type = FLOAT;
  object->value = value;
  return object;
}

enum node_type_t float_type(float_node * object)
{
  return object->type;
}

void float_print(float_node * object)
{
  printf("%f", object->value);
}

void float_destruct(float_node * object)
{
  free(object);
}