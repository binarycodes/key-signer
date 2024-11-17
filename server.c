#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include "logger.h"

const size_t MAX_CLIENT_MESSAGE_SIZE = 256;
const size_t MAX_CLIENTS_ALLOWED = 5;

int main(int argc, char *argv[]) {

  if (argc < 2) {
    log_error("no port provided");
  }

  const int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    log_error("opening socket");
  }

  const int socket_option = 1;
  setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &socket_option,
             sizeof(socket_option));

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));

  const int port_no = atoi(argv[1]);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port_no);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    log_error("on binding");
  }

  listen(sock_fd, MAX_CLIENTS_ALLOWED);

  struct sockaddr_in client_addr;
  socklen_t client_len = sizeof(client_addr);
  const int newsock_fd =
      accept(sock_fd, (struct sockaddr *)&client_addr, &client_len);
  if (newsock_fd < 0) {
    log_error("on accept");
  }

  /* read characters from the socker connection here */
  char buffer[MAX_CLIENT_MESSAGE_SIZE];

  memset(buffer, 0, sizeof(buffer));
  int n = read(newsock_fd, buffer, MAX_CLIENT_MESSAGE_SIZE);
  if (n < 0) {
    log_error("reading from socket");
  }

  printf("Here is the message...\n%s", buffer);

  n = write(newsock_fd, "message received", 17);
  if (n < 0) {
    log_error("writing to socket");
  }

  return 0;
}
