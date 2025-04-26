#include "http_error_codes.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define RESPONSE_SIZE 512

void send_error_response(connection_arguments* current_connection, int code,
                         const char* status, const char* message) {
    char response[RESPONSE_SIZE];
    int response_length = snprintf(response, sizeof(response),
                                   "HTTP/1.1 %d %s\r\n"
                                   "Content-Length: %zu\r\n"
                                   "Content-Type: text/plain\r\n"
                                   "\r\n"
                                   "%s",
                                   code, status, strlen(message), message);

    write(*current_connection->sock_fd_ptr, response, response_length);
}

void send_404(connection_arguments* current_connection) {
    send_error_response(current_connection, 404, "Not Found", "404 Not Found");
}

void send_400(connection_arguments* current_connection) {
    send_error_response(current_connection, 400, "Bad Request",
                        "400 Bad Request");
}

void send_500(connection_arguments* current_connection) {
    send_error_response(current_connection, 500, "Internal Server Error",
                        "500 Internal Server Error");
}
