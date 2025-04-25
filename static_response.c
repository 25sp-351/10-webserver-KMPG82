#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "connection_arguments.h"

#define RESPONSE_SIZE 512

void static_response(char* file_path, char* buffer, size_t file_size,
                     connection_arguments* current_connection) {
    const char* content_type = "application/octet-stream";
    if (strstr(file_path, ".png"))
        content_type = "image/png";
    else if (strstr(file_path, ".jpg") || strstr(file_path, ".jpeg"))
        content_type = "image/jpeg";

    char response[RESPONSE_SIZE];
    int response_length = snprintf(response, sizeof(response),
                                 "HTTP/1.1 200 OK\r\n"
                                 "Content-Type: %s\r\n"
                                 "Content-Length: %zu\r\n"
                                 "\r\n",
                                content_type, file_size);

    write(*current_connection->sock_fd_ptr, response, response_length);
    write(*current_connection->sock_fd_ptr, buffer, file_size);

    free(file_path);
    free(buffer);
}
