all: main

OBJS = main.o handle_connection.o usage_message.o setup_server.o error_handling.o calc_request.o calc_response.o
CC = clang
CFLAGS = -g -Wall

main: $(OBJS)
	clang -o main $(CFLAGS) $(OBJS)

main.o: main.c usage_message.h setup_server.h error_handling.h

handle_connection: handle_connection.c calc_request.h

usage_message: usage_message.c

setup_server: setup_server.c handle_connection.h

error_handling: error_handling.c

calc_request: calc_request.c calc_response.h

calc_response: calc_response.c

clean:
	rm -f main $(OBJS)
