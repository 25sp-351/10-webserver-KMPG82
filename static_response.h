#pragma once

#include <stddef.h>

#include "connection_arguments.h"

void static_response(char* file_path, char* buffer, size_t file_size,
                     connection_arguments* current_connection);
