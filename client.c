#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client.h"
#include "common.h"
#include "logger.h"

int main(int argc, char *argv[]) {

  if (argc < 3) {
    show_usage(argv[0]);
  }

  const int sock_fd = connect_to_server(argv[1], argv[2]);
  if (sock_fd < 0) {
    exit_error("connecting to server failed");
  }

  printf("Please enter the message: ");

  char buffer[MAX_MESSAGE_SIZE];
  memset(buffer, 0, MAX_MESSAGE_SIZE);
  fgets(buffer, MAX_MESSAGE_SIZE, stdin);
  buffer[strcspn(buffer, "\n")] = 0;

  int n = write_message(sock_fd, buffer);
  if (n < 0) {
    exit(1);
  }

  memset(buffer, 0, MAX_MESSAGE_SIZE);
  ks_read_message message = read_message(sock_fd);

  if (message.length < 0) {
    exit(1);
  }

  log_info(message.message);

  shutdown(sock_fd, SHUT_WR);
  close(sock_fd);
  return 0;
}

void show_usage(char *application_name) {
  const char *usage_format = "usage: %s [hostname] [port]";
  const int message_length = strlen(usage_format) + strlen(application_name);

  char *usage = (char *)malloc(sizeof(char) * message_length);
  snprintf(usage, message_length, usage_format, application_name);
  exit_error(usage);
}

int connect_to_server(char *server_hostname, char *server_port_no) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;

  struct addrinfo *result;
  int addr_result =
      getaddrinfo(server_hostname, server_port_no, &hints, &result);
  if (addr_result != 0) {
    exit_error(gai_strerror(addr_result));
  }

  int sock_fd;
  struct addrinfo *rp;
  for (rp = result; rp != NULL; rp = rp->ai_next) {
    sock_fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sock_fd == -1) {
      continue;
    }

    if (connect(sock_fd, rp->ai_addr, rp->ai_addrlen) != -1) {
      break; /* success */
    }

    close(sock_fd);
  }

  freeaddrinfo(result);

  if (rp == NULL) {
    return ERROR_RETURN_VALUE;
  }

  return sock_fd;
}
