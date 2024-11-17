#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client.h"
#include "logger.h"

const size_t MAX_MESSAGE_SIZE = 256;
const int ERROR_RETURN_VALUE = -1;

int main(int argc, char *argv[]) {

  if (argc < 3) {
    show_usage(argv[0]);
  }

  const int sock_fd = connect_to_server(argv[1], argv[2]);
  if (sock_fd < 0) {
    log_error("connecting to server failed");
  }

  printf("Please enter the message: ");

  char buffer[MAX_MESSAGE_SIZE];
  memset(buffer, 0, MAX_MESSAGE_SIZE);
  fgets(buffer, 255, stdin);

  int n = write(sock_fd, buffer, strlen(buffer));
  if (n < 0) {
    log_error("writing to socket");
  }

  memset(buffer, 0, MAX_MESSAGE_SIZE);
  n = read(sock_fd, buffer, 255);

  if (n < 0) {
    log_error("reading from socket");
  }

  printf("%s\n", buffer);
  close(sock_fd);
  return 0;
}

void show_usage(char *application_name) {
  const char *usage_format = "usage: %s [hostname] [port]";
  char *usage = (char *)malloc(
      sizeof(char) * (strlen(usage_format) + strlen(application_name)));

  snprintf(usage, strlen(usage_format) + strlen(application_name), usage_format,
           application_name);
  log_error(usage);
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
    log_error(gai_strerror(addr_result));
  }

  int sock_fd;
  struct addrinfo *rp;
  for (rp = result; rp != NULL; rp = rp->ai_next) {
    sock_fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sock_fd == -1) {
      continue;
    }

    if (connect(sock_fd, rp->ai_addr, rp->ai_addrlen) != -1) {
      break; /* Success */
    }

    close(sock_fd);
  }

  freeaddrinfo(result);

  if (rp == NULL) {
    return ERROR_RETURN_VALUE;
  }

  return sock_fd;
}
