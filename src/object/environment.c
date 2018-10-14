#include <environment.h>

unsigned long hash_string(char * key)
{
  unsigned long hash = 5381;
  int c;

  while (c = *key++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

void insert(char * key, object * value, environment ** env_map, unsigned long map_size)
{
  /* declarations */
  environment *item;
  unsigned long hash_index;

  item = allocate(environment, 1);
  item->key = key;
  item->value = value;

  /* get the hash */
  hash_index = hash_string(key) % map_size;

  /* move in array until an empty or deleted cell */
  while (env_map[hash_index] != NULL)
  {
    /* go to next cell */
    ++hash_index;

    /* wrap around the table */
    hash_index %= map_size;
  }

  env_map[hash_index] = item;
}

environment *search(char * key, environment ** env_map, unsigned long map_size)
{
  /* get the hash */
  unsigned long hash_index = hash_string(key) % map_size;

  /* move in array until an empty */
  while (env_map[hash_index] != NULL)
  {

    if (strcmp(env_map[hash_index]->key, key) == 0)
      return env_map[hash_index];

    /* go to next cell */
    ++hash_index;

    /* wrap around the table */
    hash_index %= map_size;
  }

  return NULL;
}

void delete_item(char * key, environment ** env_map, unsigned long map_size)
{
  /* declarations */
  int hash_index;

  /* get the hash */
  hash_index = hash_string(key) % map_size;

  /* move in array until an empty */
  while (env_map[hash_index] != NULL)
  {

    if (strcmp(env_map[hash_index]->key, key) == 0)
    {

      environment *item_to_delete = env_map[hash_index];
      free(item_to_delete);
      env_map[hash_index] = NULL;
      break;
    }

    /* go to next cell */
    ++hash_index;

    /* wrap around the table */
    hash_index %= map_size;
  }
}