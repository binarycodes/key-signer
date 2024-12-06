#ifndef KEYSIGNER_COMMON_H
#define KEYSIGNER_COMMON_H

#include <stdlib.h>
#include <sys/types.h>

const int ERROR_RETURN_VALUE = -1;
const size_t MAX_MESSAGE_SIZE = 1000;

typedef struct {
  const int return_value;
  const ssize_t length;
  const char *message;
} ks_read_message;

ks_read_message read_message(int socket_fd);
int write_message(int socket_fd, char *message);
#endif
