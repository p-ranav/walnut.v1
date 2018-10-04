#include <pratt_table.h>

token hash_code(token key) {
  int size = TOKEN_INVALID - TOKEN_WHITESPACE;
  return key % size;
}

pratt_function * search(token key) {
  /* get the hash */
  token hash_index = hash_code(key);

  /* move in array until an empty */
  while (hash_array[hash_index] != NULL) {

    if (hash_array[hash_index]->key == key)
      return hash_array[hash_index];

    /* go to next cell */
    ++hash_index;

    /* wrap around the table */
    hash_index %= SIZE;
  }

  return NULL;
}

void insert(token key, node *(*prefix_function)(struct parser_t *), node *(*infix_function)(struct parser_t *, node *)) {

  pratt_function * item = allocate(pratt_function, 1);
  item->key = key;
  item->prefix_function = prefix_function;
  item->infix_function = infix_function;

  /* get the hash */
  token hash_index = hash_code(key);

  /* move in array until an empty or deleted cell */
  while (hash_array[hash_index] != NULL && hash_array[hash_index]->key != -1) {
    /* go to next cell */
    ++hash_index;

    /* wrap around the table */
    hash_index %= SIZE;
  }

  hash_array[hash_index] = item;
}