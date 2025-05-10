#include "calc_request.h"

#include <stdio.h>
#include <string.h>

#include "calc_response.h"
#include "http_error_codes.h"

#define BUFFER_SIZE 200

// takes information about the current connection and the specified calc path,
// then parses and processes the path, then computes the result
void calc_request(const char* path, connection_arguments* current_connection) {
    char calc[BUFFER_SIZE];
    char operation[BUFFER_SIZE];
    int first_number    = 0;
    int second_number   = 0;
    double result       = 0.0;
    char operation_sign = '\0';
    int parsed_path     = sscanf(path, "/%[^/]/%[^/]/%d/%d", calc, operation,
                                 &first_number, &second_number);

    if (parsed_path == 4) {
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
        } else {
            send_400(current_connection);
        }

        calc_response(current_connection, first_number, operation_sign,
                      second_number, result);
    } else {
        send_400(current_connection);
    }
}
