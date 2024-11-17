#include "common.h"
#include "logger.h"
#include <string.h>
#include <unistd.h>

ks_read_message read_client_message(int socket_fd) {
  /* read characters from the socket connection here */
  char buffer[MAX_CLIENT_MESSAGE_SIZE];

  memset(buffer, 0, sizeof(buffer));
  int n = read(socket_fd, buffer, MAX_CLIENT_MESSAGE_SIZE);
  if (n < 0) {
    log_message(ERROR, "reading from socket");
    return (ks_read_message){.return_value = ERROR_RETURN_VALUE, .message = NULL};
  }

  return (ks_read_message){.return_value = 0, .message = buffer};
}

int write_client_message(int socket_fd, char *message) {
  int n = write(socket_fd, message, strlen(message));
  if (n < 0) {
    log_message(ERROR, "writing to socket");
    return ERROR_RETURN_VALUE;
  }

  return 0;
}
