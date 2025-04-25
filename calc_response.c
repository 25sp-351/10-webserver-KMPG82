#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "connection_arguments.h"

#define BODY_SIZE 200
#define RESPONSE_SIZE 512

// takes in the operands, operation, result, and information about the current
// connection, then constructs a response, and sends it to client
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
    } else {
        snprintf(body, sizeof(body), "%d %c %d = %.0f", first_number, operation,
                 second_number, result);
    }

    int body_length = strlen(body);

    char response[RESPONSE_SIZE];
    snprintf(response, RESPONSE_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/plain\r\n"
             "Content-Length: %d\r\n"
             "\r\n"
             "%s",
             body_length, body);

    write(*current_connection->sock_fd_ptr, response, RESPONSE_SIZE);
}
