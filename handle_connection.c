#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "connection_arguments.h"
#include "calc_request.h"

#define BUFFER_SIZE 200

// takes in a connection_arguments object that contains information about an
// accepted connection, then will echo each message it recieves from that
// connection if -v specified in cmd line, will close connection and free memory
// used for the connection
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
                full_line[full_line_length - 2] = '\0';  // Trim \r\n
                break;
            }
        }

        // printf("HTTP Request Line: %s\n", full_line);

        char method[BUFFER_SIZE];
        char path[BUFFER_SIZE];
        char version[BUFFER_SIZE];

        int parsed = sscanf(full_line, "%s %s %s", method, path, version);

        if (parsed == 3) {
            printf("Method: %s\n", method);
            printf("Path: %s\n", path);
            printf("Version: %s\n", version);

            //maybe separate this section to a module called process_request
            if (strcmp(method, "GET") == 0) {
                char first_word[BUFFER_SIZE];
                int matched = sscanf(path, "/%[^/]", first_word);

                // need this to have brackets
                if (strcmp(first_word, "calc") == 0)
                    calc_request(path, current_connection);
                else if (strcmp(first_word, "static") == 0)
                    printf("STATIC\n");
            } else {
                printf("ERROR\n");
            }
        } else {
            printf("ERROR\n");
        }
    }

    close(*current_connection->sock_fd_ptr);
    printf("Done with connection %d\n", *current_connection->sock_fd_ptr);
    free(full_line);
    free(current_connection);
}
