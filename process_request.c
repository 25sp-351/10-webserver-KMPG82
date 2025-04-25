#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "connection_arguments.h"
#include "calc_request.h"
#include "static_request.h"

#define BUFFER_SIZE 200

void process_request(const char* full_line,
                     connection_arguments* current_connection) {
    char method[BUFFER_SIZE];
    char path[BUFFER_SIZE];
    char version[BUFFER_SIZE];
    int number_of_extractions =
        sscanf(full_line, "%s %s %s", method, path, version);

    if (number_of_extractions == 3) {
        if (strcmp(method, "GET") == 0) {
            char first_word[BUFFER_SIZE];
            sscanf(path, "/%[^/]", first_word);

            if (strcmp(first_word, "calc") == 0)
                calc_request(path, current_connection);
            else if (strcmp(first_word, "static") == 0)
                static_request(path, current_connection);
        } else {
            printf("ERROR\n");
        }
    } else {
        printf("ERROR\n");
    }
}
