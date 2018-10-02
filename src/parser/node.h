#ifndef NODE_H
#define NODE_H
#include <node_type.h>

/* Interface functions to be implemented by
   all structs that "derive" from node */
typedef struct {
  enum node_type_t(*type)(void * node);
  void(*print)(void * node);
  void(*destruct)(void * node);
} node_interface;

/* "Base class" for all AST nodes */
struct node_t {
  /* pointer to the derived AST node type */
  void * instance; 

  /* pointer to the interface - to facilitate polymorphism */
  node_interface * interface;
};

/* construct an AST node */
struct node_t * node_construct(void * instance, node_interface * interface);

/* interface functions */
enum node_type_t node_type(struct node_t * node);
void node_print(struct node_t * node);
void node_destruct(struct node_t * node);

#endif