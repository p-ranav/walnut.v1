#ifndef INTEGER_OBJECT_H
#define INTEGER_OBJECT_H
#include <object_type.h>
#include <object.h>
#include <macros.h>

/* integer_object is an object type that represents a 32-bit integer
   This is the default integer type for type inference.

   For example:
   var a = 15;  // Here, '15' is saved as an int

*/
typedef struct
{
  enum object_type_t type; /* type = INTEGER */
  int value;               /* value = int32 value */
} integer_object;

/* construct an integer_object and assign node->value to input value */
integer_object *integer_object_construct(int obj);

/* returns the type 'INTEGER' */
enum object_type_t integer_object_type(integer_object *obj);

/* prints the integer value with printf */
char * integer_object_inspect(integer_object *obj);

/* Simply free integer_node object pointer */
void integer_object_destruct(integer_object *obj);

#endif