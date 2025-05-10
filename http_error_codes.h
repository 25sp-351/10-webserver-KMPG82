#pragma once

#include "connection_arguments.h"

void send_404(connection_arguments* current_connection);

void send_400(connection_arguments* current_connection);

void send_405(connection_arguments* current_connection);
