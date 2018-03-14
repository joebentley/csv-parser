#include <stdlib.h>

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct linked_list {
    void *node;
    struct linked_list *next;
} linked_list_t;

linked_list_t *ll_new();
linked_list_t *ll_set(linked_list_t *ll, void *data);
void *ll_get(linked_list_t *ll);
void *ll_get_and_next(linked_list_t **ll);
linked_list_t *ll_next(linked_list_t *ll);
linked_list_t **ll_push(linked_list_t **ll, void *data);
void ll_destroy(linked_list_t *ll);

#endif // LINKED_LIST_H