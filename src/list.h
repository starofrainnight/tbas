#ifndef _9M_LIST_7A75BBF9
#define _9M_LIST_7A75BBF9

#include <stdio.h>
#include <stdlib.h>

/**
 * List's node type
 */
typedef struct list_node_impl_t *list_node_t;

/**
 * List type (it's just a pointer!)
 */
typedef struct list_impl_t *list_t;

/**
 * The data deleter function type
 */
typedef void (*list_data_deleter_t)(void *data);

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create the list struct
 */
list_t list_new(list_data_deleter_t data_deleter);

/**
 * Delete the list and ensure the pointer of list be set to NULL.
 */
void list_delete(list_t *self_ptr);

/**
 * Delete the node from list and ensure the node ptr be set to NULL.
 */
void list_delete_node(list_t self, list_node_t *node_ptr);

/**
 * Prepend the data value to the list
 */
list_node_t list_prepend(list_t self, void *data);

/**
 * Append the data value to the list
 */
list_node_t list_append(list_t self, void *data);

/**
 * Get the element count of list
 */
int list_count(list_t self);

#ifdef __cplusplus
}
#endif

#endif
