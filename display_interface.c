#include "display_interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RESPONSE_SIZE 1000

// takes information about the current connection and displays the user
// interface
void display_interface(connection_arguments* current_connection) {
    const char* body =
        "Kevin Ponting's web "
        "server\n-----------------------------------------------\nUSAGE:\n1."
        "\tYou can perform an operation (addition, multiplication, or "
        "division) on two numbers if you enter a url such as the one "
        "below:\n\n\t\thttp://localhost:<port "
        "number>/calc/<operation>/<operand>/<operand>\n\n2.\tYou can access an "
        "image file from the server if you enter a url such as the one "
        "below:\n\n\t\thttp://localhost:<port number>/static/images/<file>\n\n"
        "\t\tAvailable image files:\n\t\t\tlebron.jpg\n\t\t\tcurry.jpg";

    int body_length = strlen(body);
    char response[RESPONSE_SIZE];
    int response_length = snprintf(response, RESPONSE_SIZE,
                                   "HTTP/1.1 200 OK\r\n"
                                   "Content-Length: %d\r\n"
                                   "Content-Type: text/plain\r\n"
                                   "\r\n"
                                   "%s",
                                   body_length, body);

    write(*current_connection->sock_fd_ptr, response, response_length);
}
