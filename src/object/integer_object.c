#include <integer_object.h>
#include <stdio.h>
#include <stdlib.h>

integer_object *integer_object_construct(int value)
{
  /* declarations */
  integer_object *obj;

  obj = allocate(integer_object, 1);
  obj->type = OBJECT_INTEGER;
  obj->value = value;
  return obj;
}

enum object_type_t integer_object_type(integer_object *obj)
{
  return obj->type;
}

const char * integer_object_inspect(integer_object *obj)
{
  char * value = allocate(char, 10); /* INT_MAX = 2,147,483,647, 10 digits */
  sprintf(value, "%d", obj->value);
  return value;
}

void integer_object_destruct(integer_object *obj)
{
  free(obj);
}