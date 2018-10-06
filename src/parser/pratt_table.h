#ifndef PRATT_TABLE_H
#define PRATT_TABLE_H
#include <token.h>
#include <node.h>
#include <macros.h>
#include <parser.h>
#include <stdio.h>
#include <stdlib.h>

/* Hash table for pratt parsing; hence "Pratt Table" */
typedef struct
{
  token key;                                          /* key is the token type */
  node *(*prefix_function)(struct parser_t *);        /* prefix parse function */
  node *(*infix_function)(struct parser_t *, node *); /* infix parse function */
} pratt_function;

/* define global hash table for storing pratt parser functions */
#define SIZE (TOKEN_INVALID - TOKEN_WHITESPACE)
pratt_function *hash_array[SIZE];

/* hash function for pratt table */
token hash_code(token key);

/* insert functions, i.e., our "value", into the pratt table */
void insert(token key, node *(*prefix_function)(struct parser_t *), node *(*infix_function)(struct parser_t *, node *));

/* loopup functions in pratt table */
pratt_function *search(token key);

/* delete entry in hash table */
void delete_item(token key);

#endif