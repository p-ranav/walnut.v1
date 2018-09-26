#include <list.h>

list_node_t * list_node_new(void *val) {
  list_node_t *self;
  if (!(self = LIST_MALLOC(sizeof(list_node_t))))
    return NULL;
  self->prev = NULL;
  self->next = NULL;
  self->val = val;
  return self;
}