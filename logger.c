#include "logger.h"
#include "ks_error.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *message_prefix_for_level(ks_msg_type level) {
  switch (level) {
  case ERROR:
    return "[ERROR] - ";
  case INFO:
    return "[ INFO] - ";
  default:
    return "[ INFO] - ";
  }
}

void log_message(ks_msg_type msg_level, const char *msg) {
  const char *message_prefix = message_prefix_for_level(msg_level);
  char *message_info = (char *)malloc(strlen(msg) + strlen(message_prefix));
  strncpy(message_info, message_prefix, strlen(message_prefix));
  strncat(message_info, msg, strlen(msg));

  if (msg_level == ERROR) {
    if (errno == 0) {
      fprintf(stderr, "%s\n", message_info);
    } else {
      perror(message_info);
    }
  } else {
    fprintf(stdout, "%s\n", message_info);
  }
  free(message_info);
}

void log_info(const char *msg) { log_message(INFO, msg); }
void log_error(const char *msg) { log_message(ERROR, msg); }

void exit_error(const char *msg) {
  log_message(ERROR, msg);
  exit(UNKNOWN_ERROR);
}
