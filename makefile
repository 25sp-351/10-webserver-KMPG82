all: main

OBJS = main.o handle_connection.o usage_message.o setup_server.o error_handling.o
CC = clang
CFLAGS = -g -Wall

main: $(OBJS)
	clang -o main $(CFLAGS) $(OBJS)

main.o: main.c usage_message.h setup_server.h error_handling.h

handle_connection: handle_connection.c

usage_message: usage_message.c

setup_server: setup_server.c handle_connection.h

error_handling: error_handling.c

clean:
	rm -f main $(OBJS)
