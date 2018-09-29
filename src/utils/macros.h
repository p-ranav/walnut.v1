#ifndef MACROS_H
#define MACROS_H

#define deallocate(pointer) \
  if (pointer)              \
    free(pointer);          \
  pointer = NULL;

/* Lexer macros */

#endif