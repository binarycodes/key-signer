#ifndef CUSTOM_LOGGER_H
#define CUSTOM_LOGGER_H

typedef enum { ERROR, INFO } ks_msg_type;

void log_message(ks_msg_type msg_level, const char *msg);

void log_info(const char *msg);
void log_error(const char *msg);

#endif /* CUSTOM_LOGGER_H */
