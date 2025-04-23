#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "connection_arguments.h"
#include "calc_response.h"

#define BUFFER_SIZE 200

void calc_request(char* path, connection_arguments* current_connection) {
    printf("%s\n", path);

    char calc[BUFFER_SIZE];
    char operation[BUFFER_SIZE];
    int first_number    = 0;
    int second_number   = 0;
    double result       = 0.0;
    char operation_sign = '\0';
    int path_parsed     = sscanf(path, "/%[^/]/%[^/]/%d/%d", calc, operation,
                                 &first_number, &second_number);

    if (path_parsed == 4) {
        if (strcmp(operation, "add") == 0) {
            result         = first_number + second_number;
            operation_sign = '+';
        } else if (strcmp(operation, "mult") == 0) {
            result         = first_number * second_number;
            operation_sign = '*';
        } else if (strcmp(operation, "div") == 0) {
            if (second_number != 0)
                result = (double)first_number / second_number;
            operation_sign = '/';
        }

        calc_response(current_connection, first_number, operation_sign,
                      second_number, result);
    } else {
        printf("ERROR\n");
    }
}
