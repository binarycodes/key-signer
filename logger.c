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

void log_message(ks_msg_type msg_level, const char *prefix_msg,
                 const char *msg) {

  const char *message_level_prefix = message_prefix_for_level(msg_level);

  char *message_info;
  if (prefix_msg == NULL) {
    message_info = (char *)malloc(strlen(message_level_prefix) + strlen(msg));
  } else {
    message_info = (char *)malloc(strlen(message_level_prefix) +
                                  strlen(prefix_msg) + strlen(msg));
  }

  strncpy(message_info, message_level_prefix, strlen(message_level_prefix));
  if (prefix_msg != NULL) {
    strncat(message_info, prefix_msg, strlen(prefix_msg));
  }
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

void log_info(const char *msg) { log_message(INFO, NULL, msg); }
void log_error(const char *msg) { log_message(ERROR, NULL, msg); }

void log_info_p(const char *prefix_msg, const char *msg) { log_message(INFO, prefix_msg, msg); }
void log_error_p(const char *prefix_msg, const char *msg) { log_message(ERROR, prefix_msg, msg); }

void exit_error(const char *msg) {
  log_error(msg);
  exit(UNKNOWN_ERROR);
}
