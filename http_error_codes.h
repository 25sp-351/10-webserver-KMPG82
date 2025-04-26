#pragma once

#include "connection_arguments.h"

void send_404(connection_arguments* conn);

void send_400(connection_arguments* conn);

void send_500(connection_arguments* conn);
