#ifndef OBJECT_TYPE_H
#define OBJECT_TYPE_H

/* List of all object types in the interpreter object model */
#define OBJECT_LIST \
  OBJECT(INTEGER, "integer") \
  OBJECT(BOOLEAN, "bool")\
  OBJECT(NULL, "null")

/* Enum of tokens */
enum object_type_t
{
#define OBJECT(label, string) OBJECT_##label,
  OBJECT_LIST
#undef OBJECT
  OBJECT_INVALID
};

#endif