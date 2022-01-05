#include "communication.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int read_response(int socket_fd, struct server_response *response)
{
        FILE *socket = fdopen(socket_fd, "r");

        if (socket == NULL) {
                close(socket_fd);
                fprintf(stderr, "Error opening file\n");
                return EXIT_FAILURE;
        }

        size_t response_size = 0;
        size_t size = 0;
        char *buf;

        while (getline(&buf, &size, socket) >= 0) {
                strncat(response->response, buf, size - 1);
                response_size += size;

                if (buf[RESPONSE_CODE_SIZE] == ' ') {
                        sscanf(buf, "%d", &response->response_code);
                        break;
                }
        }

        free(buf);

        return EXIT_SUCCESS;
}

int login(int socket_fd, char *user, char *password)
{
        if (user == NULL) {
                user = DEFAULT_USER;
                password = DEFAULT_PASSWORD;
        }

        size_t user_cmd_size =
                DEFAULT_USER_SIZE + USER_CMD_SIZE + CRLF_SIZE + 1;
        size_t password_cmd_size =
                DEFAULT_PASSWORD_SIZE + PASS_CMD_SIZE + CRLF_SIZE + 1;

        char *user_cmd = malloc(user_cmd_size);
        char *password_cmd = malloc(password_cmd_size);

        user_cmd[0] = '\0';
        strcat(user_cmd, USER);
        strcat(user_cmd, " ");
        strcat(user_cmd, user);
        strcat(user_cmd, CRLF);

        password_cmd[0] = '\0';
        strcat(password_cmd, PASS);
        strcat(password_cmd, " ");
        strcat(password_cmd, password);
        strcat(password_cmd, CRLF);

        if (send_cmd(socket_fd, user_cmd, user_cmd_size)) {
                fprintf(stderr, "Error sending user\n");
                free(user_cmd);
                free(password_cmd);
                return EXIT_FAILURE;
        }

        free(user_cmd);
        struct server_response response;

        if (read_response(socket_fd, &response)) {
                fprintf(stderr, "Error reading server response!\n");
                free(password_cmd);
                return EXIT_FAILURE;
        }

        if (response.response_code != USERNAME_OK) {
                fprintf(stderr, "Error with username.\nResponse: %d - %s\n",
                        response.response_code, response.response);
                free(password_cmd);
                return EXIT_FAILURE;
        }

        if (send_cmd(socket_fd, password_cmd, password_cmd_size)) {
                fprintf(stderr, "Error sending password\n");
                free(password_cmd);
                return EXIT_FAILURE;
        }

        free(password_cmd);
        memset(&response, 0, sizeof(struct server_response));

        if (read_response(socket_fd, &response)) {
                fprintf(stderr, "Error reading server response!\n");
                return EXIT_FAILURE;
        }

        if (response.response_code != LOGIN_SUCCESS) {
                fprintf(stderr, "Error with password.\nResponse: %d - %s\n",
                        response.response_code, response.response);
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

int send_cmd(int socket_fd, char *cmd, size_t cmd_size)
{
        if (write(socket_fd, cmd, cmd_size) != cmd_size) {
                fprintf(stderr, "Error writing command!\n");
                perror("write");
                return EXIT_FAILURE;
        }

        if (write(socket_fd, CRLF, CRLF_SIZE) != CRLF_SIZE) {
                fprintf(stderr, "Error writing command terminator\n");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}
