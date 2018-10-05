#include <string_node.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string_node * string_construct(char * value)
{
  /* declarations */
  int value_length;

  string_node * object = allocate(string_node, 1);
  object->type = STRING;
  value_length = strlen(value);
  object->value = allocate(char, value_length);
  strcpy(object->value, value);
  return object;
}

enum node_type_t string_type(string_node * object)
{
  return object->type;
}

void string_print(string_node * object)
{
  printf("\"%s\"", object->value);
}

void string_destruct(string_node * object)
{
  free(object);
}