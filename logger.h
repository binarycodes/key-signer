#ifndef CUSTOM_LOGGER_H
#define CUSTOM_LOGGER_H

typedef enum {
  ERROR,
  INFO
} MSG_LEVEL;

void log_message(MSG_LEVEL msg_level, const char *msg);

void log_info(const char *msg);
void log_error(const char *msg);

#endif /* CUSTOM_LOGGER_H */
