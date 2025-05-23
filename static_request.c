#include "static_request.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "static_response.h"
#include "http_error_codes.h"

#define STATIC_PREFIX_LENGTH 7

// takes in the specified path from the request and information about the
// current connection, then fetches the image the client wants
void static_request(const char* path,
                    connection_arguments* current_connection) {
    const char* relative_path = path + STATIC_PREFIX_LENGTH;
    int file_path_length      = strlen(path) + 2;
    char* file_path           = malloc(file_path_length);

    snprintf(file_path, file_path_length, "./static%s", relative_path);

    int file = open(file_path, O_RDONLY);
    if (file < 0) {
        send_404(current_connection);
        free(file_path);
        return;
    }

    struct stat file_stat;
    fstat(file, &file_stat);

    size_t file_size = file_stat.st_size;

    char* buffer     = malloc(file_size);
    read(file, buffer, file_size);

    close(file);

    static_response(file_path, buffer, file_size, current_connection);
}
