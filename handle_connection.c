#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "connection_arguments.h"

#define BUFFER_SIZE 5
#define BUFFER_MULTIPLIER 2

// takes in a connection_arguments object that contains information about an
// accepted connection, then will echo each message it recieves from that
// connection if -v specified in cmd line, will close connection and free memory
// used for the connection
void handle_connection(void* connection) {
    connection_arguments* current_connection =
        (connection_arguments*)connection;

    printf("Handling connection on %d\n", *current_connection->sock_fd_ptr);

    char buffer[BUFFER_SIZE];
    char* full_line        = malloc(BUFFER_SIZE);
    int full_line_length   = 0;
    int full_line_capacity = BUFFER_SIZE;
    int bytes_read         = 0;

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        bytes_read =
            read(*current_connection->sock_fd_ptr, buffer, BUFFER_SIZE);

        if (bytes_read > 0) {
            for (int ix = 0; ix < bytes_read; ++ix) {
                if (full_line_length + 1 >= full_line_capacity) {
                    full_line_capacity *= BUFFER_MULTIPLIER;
                    char* new_line = realloc(full_line, full_line_capacity);
                    full_line      = new_line;
                }

                full_line[full_line_length++] = buffer[ix];

                if (buffer[ix] == '\n') {
                    full_line[full_line_length] = '\0';

                    if (current_connection->should_print_messages == 1)
                        write(*current_connection->sock_fd_ptr, full_line,
                              full_line_length);

                    full_line_length = 0;
                }
            }

            continue;
        }

        break;
    }

    free(full_line);
    close(*current_connection->sock_fd_ptr);
    printf("Done with connection %d\n", *current_connection->sock_fd_ptr);
    free(current_connection);
}
