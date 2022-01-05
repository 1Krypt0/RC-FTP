#ifndef RCOM_MESSAGES_H_
#define RCOM_MESSAGES_H_

#include <stddef.h>

struct server_response {
        char response[1024];
        int response_code;
};

int send_cmd(int socket_fd, char *cmd, size_t cmd_size);

int read_response(int socket_fd, struct server_response *response);

int login(int socket_fd, char *user, char *password);

int enter_passive_mode(int socket_fd, struct server_response *response);

int convert_to_port(char *response, char *ip, int *port);

#endif // RCOM_MESSAGES_H_
