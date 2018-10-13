#ifndef BOOLEAN_OBJECT_H
#define BOOLEAN_OBJECT_H
#include <object_type.h>
#include <object.h>
#include <macros.h>

typedef struct
{
  enum object_type_t type; /* type = BOOLEAN */
  int value;               /* value = bool value */
} boolean_object;

boolean_object *boolean_object_construct(int obj);

enum object_type_t boolean_object_type(boolean_object *obj);
const char * boolean_object_inspect(boolean_object *obj);
void boolean_object_destruct(boolean_object *obj);

#endif