#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char*** csv_data;

typedef struct linked_list {
    void *node;
    struct linked_list *next;
} linked_list_t;

linked_list_t *ll_new() {
    linked_list_t *ll = malloc(sizeof(linked_list_t));
    ll->node = NULL;
    ll->next = NULL;
    return ll;
}

linked_list_t *ll_set(linked_list_t *ll, void *data) {
    ll->node = data;
    return ll;
}

void *ll_get(linked_list_t *ll) {
    return ll->node;
}

void *ll_get_and_next(linked_list_t **ll) {
    linked_list_t *old = *ll;
    *ll = (*ll)->next;
    return old->node;
}

linked_list_t *ll_next(linked_list_t *ll) {
    return ll->next;
}

linked_list_t **ll_push(linked_list_t **ll, void *data) {
    (*ll)->node = data;
    (*ll)->next = ll_new();
    *ll = (*ll)->next;
    return ll;
}

void ll_destroy(linked_list_t *ll) {
    while (ll->next != NULL) {
        linked_list_t *current = ll;
        ll = ll->next;
        free(current);
    }
    free(ll);
}

int main(int argc, char *argv[]) {
    // FILE *file = fopen("test.csv", "r");
    // char buf[100];

    // while (fgets(buf, sizeof buf, file) != NULL) {
    //     char *token = strtok(buf, ",");
    //     while ((token = strtok(NULL, ","))) {
    //         printf("%s\n", token);
    //     }
    // }

    linked_list_t *ll = ll_new();
    linked_list_t *begin = ll;

    int a = 1;
    int b = 2;
    int c = 3;

    ll_push(&ll, &a);
    ll_push(&ll, &b);
    ll_push(&ll, &c);

    ll = begin;

    while (ll->next) {
        printf("%d\n", *(int*)ll_get_and_next(&ll));
    }

    ll_destroy(ll);

    return 0;
}