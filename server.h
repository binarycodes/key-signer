#ifndef KEYSIGNER_SERVER_H
#define KEYSIGNER_SERVER_H

#include <stdlib.h>

const size_t MAX_CLIENTS_ALLOWED = 5;

void handle_sigterm(int signal);
void show_usage(char *application_name);

int create_server_socket();
void shutdown_and_close_socket(int socket_fd);

#endif /* KEYSIGNER_SERVER_H */
