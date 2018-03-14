#include <stdio.h>
#include "csv_parser.h"

int main(int argc, char *argv[]) {
    FILE *file = fopen("test.csv", "r");

    csv_data_t *data = csv_read_from_file(file);

    // for (uint32_t i = 0; i < data->num_rows; ++i)
    // for (uint32_t j = 0; j < data->num_columns; ++j)
    //     printf("%s\n", data->data[i][j]);

    csv_destroy(data);

    return 0;
}