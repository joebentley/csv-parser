#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct csv_data {
    char ***data;
    uint32_t num_rows;
    uint32_t num_columns;
} csv_data_t;

csv_data_t *csv_read_from_file(FILE *file) {
    char buf[1000];
    uint32_t num_rows = 0;
    uint32_t num_columns = 0;
    linked_list_t *rows = ll_new();
    linked_list_t *begin = rows;

    while (fgets(buf, sizeof buf, file) != NULL) {
        linked_list_t *row = ll_new();
        linked_list_t *begin_row = row;
        char *line = malloc(sizeof(char) * strlen(buf) + 1);
        char *token;
        char *separator = NULL;

        memcpy(line, buf, strlen(buf) + 1);

        do {
            separator = strpbrk(line, ",\n");
            token = line;
            
            if (separator) {
                line = separator + 1;
                *separator = '\0';
            }

            ll_push(&row, token);
            // printf("%p: %s\n", token, token);
            if (num_rows == 0)
                ++num_columns;
        } while (separator);

        ll_push(&rows, begin_row);
        ++num_rows;
    }

    rows = begin;

    csv_data_t *csv = malloc(sizeof(csv_data_t));
    csv->data = malloc(sizeof(char*) * num_rows);
    csv->num_columns = num_columns;
    csv->num_rows = num_rows;

    for (uint32_t i = 0; i < num_rows; ++i) {
        csv->data[i] = malloc(sizeof(char*) * num_columns);
    }

    for (uint32_t i = 0; i < num_rows; ++i) {
        linked_list_t *row = ll_get_and_next(&rows);
        linked_list_t *begin_row = row;

        for (uint32_t j = 0; j < num_columns; ++j) {
            char *element = ll_get_and_next(&row);
            // printf("%d %d: %p %s\n", i, j, element, element);
            csv->data[i][j] = element;
        }
        ll_destroy(begin_row);
    }

    ll_destroy(begin);

    return csv;
}

void csv_destroy(csv_data_t *data) {
    for (uint32_t i = 0; i < data->num_rows; ++i) {
        free(*data->data[i]); // Free the string
        free(data->data[i]); // Free the pointer to the string
    }
    free(data);
}

int main(int argc, char *argv[]) {
    FILE *file = fopen("test.csv", "r");

    csv_data_t *data = csv_read_from_file(file);

    for (uint32_t i = 0; i < data->num_rows; ++i)
    for (uint32_t j = 0; j < data->num_columns; ++j)
        printf("%s\n", data->data[i][j]);

    csv_destroy(data);

    // printf("%d %d\n", data->num_rows, data->num_columns);


    // for (uint32_t i = 0; i < data->num_rows; ++i)
    // for (uint32_t j = 0; j < data->num_columns; ++j) {
    //     printf("%p: %s\n", data->data[i][j], data->data[i][j]);
    // }

    // char buf[100];

    // while (fgets(buf, sizeof buf, file) != NULL) {
    //     char *token = strtok(buf, ",");
    //     while ((token = strtok(NULL, ","))) {
    //         printf("%s\n", token);
    //     }
    // }

    // linked_list_t *ll = ll_new();
    // linked_list_t *begin = ll;

    // int a = 1;
    // int b = 2;
    // int c = 3;

    // ll_push(&ll, &a);
    // ll_push(&ll, &b);
    // ll_push(&ll, &c);

    // ll = begin;

    // while (ll->next) {
    //     printf("%d\n", *(int*)ll_get_and_next(&ll));
    // }

    // ll_destroy(ll);

    return 0;
}