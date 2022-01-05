#ifndef RCOM_MESSAGES_H_
#define RCOM_MESSAGES_H_

#include <stddef.h>

struct server_response {
        char response[1024];
        int response_code;
};

int read_response(int socket_fd, struct server_response *response);

int send_cmd(int socket_fd, char *cmd, size_t cmd_size);

int login(int socket_fd, char *user, char *password);

#endif // RCOM_MESSAGES_H_
