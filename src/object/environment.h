#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <object.h>
#include <macros.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  char * key;
  object * value;
} environment;

unsigned long hash_string(char * key);
void insert(char * key, object * value, environment ** env_map, unsigned long map_size);
environment *search(char * key, environment ** env_map, unsigned long map_size);
void delete(char * key, environment ** env_map, unsigned long map_size);

#endif