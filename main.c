#include <stdio.h>
#include <string.h>

#include "error_handling.h"
#include "setup_server.h"
#include "usage_message.h"

#define DEFAULT_PORT 1025

// takes in cmd line arguments, sets default port, sets if messages should be
// echo'd, and valides the input
int main(int argc, char* argv[]) {
    int should_print_messages = 0;
    int port_number           = DEFAULT_PORT;

    if (argc > 4) {
        usage_message();
        return 0;
    }

    for (int ix = 1; ix < argc; ix++) {
        if (strcmp(argv[ix], "-v") == 0) {
            should_print_messages = 1;
            continue;
        }

        if (strcmp(argv[ix], "-p") == 0) {
            if (argc <= ix + 1 ||
                validate_port_number(argv[ix + 1], &port_number) ||
                check_additional_characters(argv[ix + 1])) {
                usage_message();
                return 0;
            }

            continue;
        }
    }

    setup_server(port_number, should_print_messages);

    return 0;
}
