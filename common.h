#ifndef KEYSIGNER_COMMON_H
#define KEYSIGNER_COMMON_H

#include <stdlib.h>

const int ERROR_RETURN_VALUE = -1;
const size_t MAX_CLIENT_MESSAGE_SIZE = 256;

typedef struct {
  const int return_value;
  const char *message;
} ks_read_message;

ks_read_message read_client_message(int socket_fd);
int write_client_message(int socket_fd, char *message);

#endif
