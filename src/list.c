struct list_node_impl_t;
struct list_impl_t;

#include "list.h"
#include <memory.h>
#include "common.h"
#include "uthash/utlist.h"

typedef struct list_node_impl_t {
  void *data;
  list_node_t prev;
  list_node_t next;
} list_node_impl_t;

typedef struct list_impl_t {
  list_node_t head;
  list_data_deleter_t data_deleter;
} list_impl_t;

void *list_node_get_data(list_node_t self) {
  ENSURE(self != 0);
  return self->data;
}

list_node_t list_node_get_prev(list_node_t self) {
  ENSURE(self != 0);
  return self->prev;
}

list_node_t list_node_get_next(list_node_t self) {
  ENSURE(self != 0);
  return self->next;
}

list_t list_new(list_data_deleter_t data_deleter) {
  list_t self = 0;

  safe_maclloc(list_impl_t, self);
  self->data_deleter = data_deleter;

  return self;
};

void list_delete(list_t *self_ptr) {
  if ((0 == self_ptr) || (0 == *self_ptr)) {
    return;
  }
  list_node_t head = (*self_ptr)->head;
  list_node_t elt = 0;
  list_node_t tmp = 0;

  DL_FOREACH_SAFE(head, elt, tmp) { list_delete_node(*self_ptr, &elt); }

  safe_free(self_ptr);
}

static list_node_t list_new_node(list_t self, void *data) {
  list_node_t node = 0;

  safe_maclloc(list_node_impl_t, node);

  return node;
}

void list_delete_node(list_t self, list_node_t *node_ptr) {
  if ((0 == self) || (0 == node_ptr) || (0 == *node_ptr)) {
    return;
  }

  list_node_t node = *node_ptr;

  if (self->data_deleter) {
    self->data_deleter(node->data);
  }

  DL_DELETE(self->head, node);
  safe_free(node_ptr);
}

list_node_t list_prepend(list_t self, void *data) {
  ENSURE(self != 0);

  list_node_t node = list_new_node(self, data);
  DL_PREPEND(self->head, node);

  return node;
}

list_node_t list_append(list_t self, void *data) {
  ENSURE(self != 0);

  list_node_t node = list_new_node(self, data);
  DL_APPEND(self->head, node);

  return node;
}

int list_count(list_t self) {
  ENSURE(self != 0);

  int count = 0;
  list_node_t el = NULL;

  DL_COUNT(self->head, el, count);

  return count;
}
