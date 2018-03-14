#include <stdio.h>
#include <stdlib.h>

#ifndef CSV_PARSER_H_
#define CSV_PARSER_H_

typedef struct csv_data {
    char ***data;
    uint32_t num_rows;
    uint32_t num_columns;
} csv_data_t;

csv_data_t *csv_read_from_file(FILE *file);
void csv_destroy(csv_data_t *data);

#endif // CSV_PARSER_H_