#ifndef RETURN_OBJECT_H
#define RETURN_OBJECT_H
#include <object_type.h>
#include <object.h>
#include <macros.h>

typedef struct
{
  enum object_type_t type; /* type = RETURN */
  object * value;          /* value = returned object */
} return_object;

return_object *return_object_construct();

enum object_type_t return_object_type(return_object *obj);
const char * return_object_inspect(return_object *obj);
void return_object_destruct(return_object *obj);

#endif