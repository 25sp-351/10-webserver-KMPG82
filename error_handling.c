#include <stdio.h>
#include <string.h>

#define LOWER_BOUND_PORT 1024

// takes in a string as input, if the string has additional trailing characters,
// returns 0, else returns 1
int check_additional_characters(const char *buffer) {
    int length_parsed;

    sscanf(buffer, "%*d%n", &length_parsed);

    return (strlen(buffer) - length_parsed != 0);
}

// takes in a string and integer as input, returns 0 if the string contains a
// port number greater than 1024, else returns 1
int validate_port_number(const char *buffer, int *port_number) {
    return (!sscanf(buffer, "%d", port_number) ||
            *port_number <= LOWER_BOUND_PORT);
}
