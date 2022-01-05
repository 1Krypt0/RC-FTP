#ifndef RCOM_CONNECTION_H_
#define RCOM_CONNECTION_H_

#include <stddef.h>

int send_cmd(int socket_fd, char *cmd, size_t cmd_size);

#endif // RCOM_CONNECTION_H_
