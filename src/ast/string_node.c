#include <string_node.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string_node * string_construct(char * value)
{
  /* declarations */
  int value_length;
  string_node * object;

  object = allocate(string_node, 1);
  object->type = STRING;

  /* string copy input argument to object->value */
  value_length = strlen(value);
  object->value = allocate(char, value_length + 1);
  strcpy(object->value, value);
  object->value[value_length] = '\0'; /* null terminate */

  return object;
}

enum node_type_t string_type(string_node * object)
{
  return object->type;
}

void string_print(string_node * object)
{
  /* print string with double quotes */
  printf("\"%s\"", object->value);
}

void string_destruct(string_node * object)
{
  /* free up character array in object */
  free(object->value);

  /* free up string_node pointer */
  free(object);
}