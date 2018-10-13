#include <object.h>
#include <macros.h>

#include <stdlib.h>

object *object_construct(void *instance, object_interface *interface)
{
  /* declarations */
  object *obj;

  obj = allocate(object, 1);
  obj->instance = instance;
  obj->interface = interface;
  return obj;
}

enum object_type_t object_type(object *obj)
{
  /* call the *_type(...) of the derived type */
  return (obj->interface->type)(obj->instance);
}

const char * object_inspect(object *obj)
{
  /* call the *_inspect(...) of the derived type */
  return (obj->interface->inspect)(obj->instance);
}

void object_destruct(object *obj)
{
  /* call the *_destruct(...) of the derived type */
  (obj->interface->destruct)(obj->instance);

  /* free up the interface table */
  free(obj->interface);

  /* finally, free up node pointer */
  free(obj);
}