#include <string.h>
#include "csv_parser.h"
#include "linked_list.h"

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
        free(data->data[i]); // Free the columns at row i
    }
    free(data->data); // Free the rows
    free(data);
}