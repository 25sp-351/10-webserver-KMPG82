#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "connection_arguments.h"
#include "handle_connection.h"

#define LISTEN_BACKLOG 1

// takes in two integers, one for port number and one that specifies if messages
// should be echo'd, then establishes the server and waits for incoming
// connection requests, will create a thread for each accepted connection
void setup_server(int port_number, int should_print_messages) {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in socket_address;
    memset(&socket_address, '\0', sizeof(socket_address));
    socket_address.sin_family      = AF_INET;
    socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address.sin_port        = htons(port_number);

    printf("Binding to port %d\n", port_number);

    int return_val;
    return_val = bind(socket_fd, (struct sockaddr*)&socket_address,
                      sizeof(socket_address));

    if (return_val < 0) {
        perror("Bind error");
        return;
    }

    return_val = listen(socket_fd, LISTEN_BACKLOG);

    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    while (1) {
        pthread_t thread;
        int* client_fd_buf               = malloc(sizeof(int));
        connection_arguments* connection = malloc(sizeof(connection_arguments));
        connection->should_print_messages = should_print_messages;

        *client_fd_buf = accept(socket_fd, (struct sockaddr*)&client_address,
                                &client_address_len);

        connection->sock_fd_ptr = client_fd_buf;

        printf("Accepted connection on %d\n", *connection->sock_fd_ptr);

        pthread_create(&thread, NULL, (void* (*)(void*))handle_connection,
                       (void*)connection);
    }
}
