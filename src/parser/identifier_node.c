#include <identifier_node.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node_interface *IDENTIFIER_AS_NODE = &(node_interface)
{
  .type = (enum node_type_t(*)(void *)) identifier_type,
  .print = (void(*)(void*)) identifier_print,
  .destruct = (void(*)(void *)) identifier_destruct
};

identifier_node * identifier_construct(char * name)
{
  identifier_node * object = allocate(identifier_node, 1);
  object->type = IDENTIFIER;
  int name_length = strlen(name);
  object->value = allocate(char, name_length);
  strcpy(object->value, name);
  return object;
}

enum node_type_t identifier_type(identifier_node * object)
{
  return IDENTIFIER;
}

void identifier_print(identifier_node * object)
{
  printf("%s", object->value);
}

void identifier_destruct(identifier_node * object)
{
  free(object);
}