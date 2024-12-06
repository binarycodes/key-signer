#include "common.h"
#include "logger.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

ks_read_message read_message(int socket_fd) {
  /* read characters from the socket connection here */
  char *buffer = malloc(sizeof(char) * MAX_MESSAGE_SIZE);

  memset(buffer, 0, MAX_MESSAGE_SIZE);
  int n = read(socket_fd, buffer, MAX_MESSAGE_SIZE);
  if (n < 0) {
    log_error("reading from socket");
    return (ks_read_message){
        .return_value = ERROR_RETURN_VALUE, .message = NULL, .length = n};
  }
  return (ks_read_message){.return_value = 0, .message = buffer, .length = n};
}

int write_message(int socket_fd, char *message) {
  int n = write(socket_fd, message, strlen(message));
  if (n < 0) {
    log_error("writing to socket");
    return ERROR_RETURN_VALUE;
  }

  return 0;
}
