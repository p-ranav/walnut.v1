#ifndef NULL_OBJECT_H
#define NULL_OBJECT_H
#include <object_type.h>
#include <object.h>
#include <macros.h>

typedef struct
{
  enum object_type_t type; /* type = NULL */
} null_object;

null_object *null_object_construct();

enum object_type_t null_object_type(null_object *obj);
const char * null_object_inspect(null_object *obj);
void null_object_destruct(null_object *obj);

#endif