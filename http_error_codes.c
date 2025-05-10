#include "http_error_codes.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define RESPONSE_SIZE 512
#define NOT_FOUND_CODE 404
#define BAD_REQUEST_CODE 400
#define INTERNAL_SERVER_ERROR_CODE 500
#define NOT_ALLOWED_CODE 405

// takes information about the current connection, the error code, status, and
// message, then constructs a response to be sent to the client
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

// takes in information about the current connection, then initializes
// parameters for a 404 error
void send_404(connection_arguments* current_connection) {
    send_error_response(current_connection, NOT_FOUND_CODE, "Not Found",
                        "404 Not Found");
}

// takes in information about the current connection, then initializes
// parameters for a 400 error
void send_400(connection_arguments* current_connection) {
    send_error_response(current_connection, BAD_REQUEST_CODE, "Bad Request",
                        "400 Bad Request");
}

// takes in information about the current connection, then initializes
// parameters for a 405 error
void send_405(connection_arguments* current_connection) {
    send_error_response(current_connection, NOT_ALLOWED_CODE, "Not Allowed",
                        "405 Not Allowed");
}
