#ifndef INTEGER_OBJECT_H
#define INTEGER_OBJECT_H
#include <object_type.h>
#include <object.h>
#include <macros.h>

typedef struct
{
  enum object_type_t type; /* type = INTEGER */
  int value;               /* value = int32 value */
} integer_object;

integer_object *integer_object_construct(int obj);

enum object_type_t integer_object_type(integer_object *obj);
const char * integer_object_inspect(integer_object *obj);
void integer_object_destruct(integer_object *obj);

#endif