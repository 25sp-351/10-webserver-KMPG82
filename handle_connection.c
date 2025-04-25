#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "connection_arguments.h"
#include "process_request.h"

#define BUFFER_SIZE 200

// takes in a connection_arguments object that contains information about an
// accepted connection, then will echo each message it recieves from that
// connection, will close connection and free memory used for the connection
void handle_connection(void* connection) {
    connection_arguments* current_connection =
        (connection_arguments*)connection;

    printf("Handling connection on %d\n", *current_connection->sock_fd_ptr);

    char buffer[BUFFER_SIZE];
    char* full_line      = malloc(BUFFER_SIZE);
    int full_line_length = 0;
    int bytes_read       = 0;

    bytes_read = read(*current_connection->sock_fd_ptr, buffer, BUFFER_SIZE);

    if (bytes_read > 0) {
        for (int ix = 0; ix < bytes_read; ++ix) {
            full_line[full_line_length++] = buffer[ix];

            if (full_line_length >= 2 &&
                full_line[full_line_length - 2] == '\r' &&
                full_line[full_line_length - 1] == '\n') {
                full_line[full_line_length - 2] = '\0';
                break;
            }
        }

        process_request(full_line, current_connection);
    }

    printf("Done with connection %d\n", *current_connection->sock_fd_ptr);

    close(*current_connection->sock_fd_ptr);
    free(full_line);
    free(current_connection);
}
