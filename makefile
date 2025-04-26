all: main

OBJS = main.o handle_connection.o usage_message.o setup_server.o error_handling.o calc_request.o calc_response.o static_request.o process_request.o static_response.o display_interface.o
CC = clang
CFLAGS = -g -Wall

main: $(OBJS)
	clang -o main $(CFLAGS) $(OBJS)

main.o: main.c usage_message.h setup_server.h error_handling.h

handle_connection: handle_connection.c process_request.h

usage_message: usage_message.c

setup_server: setup_server.c handle_connection.h

error_handling: error_handling.c

calc_request: calc_request.c calc_response.h

calc_response: calc_response.c

static_request: static_request.c static_response.h

static_response: static_response.c

process_request: process_request.c calc_request.h static_request.h display_interface.h

display_interface: display_interface.c

clean:
	rm -f main $(OBJS)
