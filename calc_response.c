#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "connection_arguments.h"

#define BODY_SIZE 200

void calc_response(connection_arguments* current_connection, int first_number,
                   char operation, int second_number, double result) {
    char body[BODY_SIZE];

    if (operation == '/') {
        if (second_number == 0) {
            snprintf(body, sizeof(body), "ERROR");
        } else {
            snprintf(body, sizeof(body), "%d %c %d = %.2f", first_number,
                     operation, second_number, result);
        }
    } else if (operation == '\0') {
        snprintf(body, sizeof(body), "ERROR");
    } else {
        snprintf(body, sizeof(body), "%d %c %d = %.0f", first_number, operation,
                 second_number, result);
    }

    int body_len     = strlen(body);

    int response_len = snprintf(NULL, 0,
                                "HTTP/1.1 200 OK\r\n"
                                "Content-Type: text/plain\r\n"
                                "Content-Length: %d\r\n"
                                "\r\n"
                                "%s",
                                body_len, body);

    char* response   = malloc(response_len + 1);

    snprintf(response, response_len + 1,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/plain\r\n"
             "Content-Length: %d\r\n"
             "\r\n"
             "%s",
             body_len, body);

    printf("THIS IS THE RESPONSE %s\n", response);

    write(*current_connection->sock_fd_ptr, response, response_len);

    free(response);
}
