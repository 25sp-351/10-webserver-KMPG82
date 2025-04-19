#include <stdio.h>

// prints usage message
void usage_message() {
    printf(
        "Invalid input. If port number is specified, use one greater than "
        "1024, and must be after -p. For exmaple: ./main -p <port number> "
        "-v\n");
}
