#ifndef OBJECT_H
#define OBJECT_H
#include <object_type.h>

/* Interface functions to be implemented by
   all structs that "derive" from object */
typedef struct
{
  enum object_type_t(*type)(void *object);
  const char *(*inspect)(void *object);
  void(*destruct)(void *object);
} object_interface;

/* Base-class to all object types in the 
   interpreter's object engine */
typedef struct {
  /* pointer to the derived AST node type */
  void *instance;

  /* pointer to the interface - to facilitate polymorphism */
  object_interface *interface;
} object;

/* construct an object */
object *object_construct(void *instance, object_interface *interface);

/* interface functions */
enum object_type_t object_type(object *obj);
const char * object_inspect(object *obj);
void object_destruct(object *obj);

#endif