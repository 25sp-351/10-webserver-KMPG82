#pragma once

#include "connection_arguments.h"

void process_request(const char* full_line,
                     connection_arguments* current_connection);
