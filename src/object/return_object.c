#include <return_object.h>
#include <stdio.h>
#include <stdlib.h>

return_object *return_object_construct()
{
  /* declarations */
  return_object *obj;

  obj = allocate(return_object, 1);
  obj->type = OBJECT_RETURN;
  obj->value = NULL;
  return obj;
}

enum object_type_t return_object_type(return_object *obj)
{
  return obj->type;
}

const char * return_object_inspect(return_object *obj)
{
  return object_inspect(obj->value);
}

void return_object_destruct(return_object *obj)
{
  free(obj);
}