#include <bool_object.h>
#include <stdio.h>
#include <stdlib.h>

boolean_object *boolean_object_construct(int value)
{
  /* declarations */
  boolean_object *obj;

  obj = allocate(boolean_object, 1);
  obj->type = OBJECT_BOOLEAN;
  obj->value = (value > 1) ? 1 : 0;
  return obj;
}

enum object_type_t boolean_object_type(boolean_object *obj)
{
  return obj->type;
}

const char * boolean_object_inspect(boolean_object *obj)
{
  return (obj->value > 0) ? "true" : "false";
}

void boolean_object_destruct(boolean_object *obj)
{
  free(obj);
}