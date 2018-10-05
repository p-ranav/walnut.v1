#include <identifier_node.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

identifier_node * identifier_construct(char * name)
{
  /* declarations */
  int name_length;

  identifier_node * object = allocate(identifier_node, 1);
  object->type = IDENTIFIER;
  name_length = strlen(name);
  object->value = allocate(char, name_length + 1);
  strcpy(object->value, name);
  object->value[name_length] = '\0';
  return object;
}

enum node_type_t identifier_type(identifier_node * object)
{
  return object->type;
}

void identifier_print(identifier_node * object)
{
  printf("%s", object->value);
}

void identifier_destruct(identifier_node * object)
{
  free(object->value);
  free(object);
}