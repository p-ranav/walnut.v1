#ifndef MACROS_H
#define MACROS_H

#define trace printf
#define error printf

#define deallocate(pointer) \
  if(pointer)\
    free(pointer);\
  pointer = NULL;

#endif