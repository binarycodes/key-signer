#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include "common.h"
#include "logger.h"
#include "server.h"

int main(int argc, char *argv[]) {

  struct sigaction sa = {.sa_handler = &handle_sigterm};
  sigaction(SIGTERM, &sa, NULL);
  sigaction(SIGINT, &sa, NULL);

  if (argc < 2) {
    show_usage(argv[0]);
  }

  const int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    log_error("on socket open");
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
    log_error("on socket bind");
  }

  if (listen(sock_fd, MAX_CLIENTS_ALLOWED) < 0) {
    log_error("on listen");
  }

  while (true) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    const int connection_fd =
        accept(sock_fd, (struct sockaddr *)&client_addr, &client_len);
    if (connection_fd < 0) {
      log_error("on accept");
    }

    ks_read_message read_message = read_client_message(connection_fd);
    if (read_message.return_value == ERROR_RETURN_VALUE) {
      exit(1);
    }

    printf("Here is the message...\n%s", read_message.message);

    int result = write_client_message(connection_fd, "message received");

    if (result == ERROR_RETURN_VALUE) {
      exit(1);
    }

    /* close client connection */
    close(connection_fd);
  }

  return 0;
}

void show_usage(char *application_name) {
  const char *usage_format = "usage: %s [port]";
  char *usage = (char *)malloc(
      sizeof(char) * (strlen(usage_format) + strlen(application_name)));

  snprintf(usage, strlen(usage_format) + strlen(application_name), usage_format,
           application_name);
  log_error(usage);
}

void handle_sigterm(int signal) {
  fprintf(stdout, "\n");
  log_info("cleaning up process state ...");
  log_info("exiting process now...");
  exit(0);
}
