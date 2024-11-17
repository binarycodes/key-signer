#include "logger.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *fixed_message_for_level(MSG_LEVEL level) {
  switch (level) {
  case ERROR:
    return "[ERROR] - ";
  case INFO:
    return "[INFO ] - ";
  default:
    return "[INFO ] - ";
  }
}

void log_message(MSG_LEVEL msg_level, const char *msg) {
  const char *fixed_msg = fixed_message_for_level(msg_level);
  char *message_info = (char *)malloc(strlen(msg) + strlen(fixed_msg));
  strncpy(message_info, fixed_msg, strlen(fixed_msg));
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

void log_error(const char *msg) {
  log_message(ERROR, msg);
  exit(1);
}
