#include <null_object.h>
#include <stdio.h>
#include <stdlib.h>

extern const char *const object_strings[]; /* used in null_object_inspect */

null_object *null_object_construct()
{
  /* declarations */
  null_object *obj;

  obj = allocate(null_object, 1);
  obj->type = OBJECT_NULL;
  return obj;
}

enum object_type_t null_object_type(null_object *obj)
{
  return obj->type;
}

const char * null_object_inspect(null_object *obj)
{
  return object_strings[obj->type];
}

void null_object_destruct(null_object *obj)
{
  free(obj);
}