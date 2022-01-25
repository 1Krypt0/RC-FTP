#include "communication.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int send_cmd(int socket_fd, char *cmd, int cmd_size)
{
        if (write(socket_fd, cmd, cmd_size) != cmd_size) {
                fprintf(stderr, "Error writing command!\n");
                perror("write");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

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

        size_t user_cmd_size = strlen(user) + USER_CMD_SIZE + CRLF_SIZE + 1;
        size_t password_cmd_size =
                strlen(password) + PASS_CMD_SIZE + CRLF_SIZE + 1;

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

int enter_passive_mode(int socket_fd, struct server_response *response)
{
        int pasv_cmd_size = PASV_CMD_SIZE + CRLF_SIZE;
        char *pasv_cmd = malloc(pasv_cmd_size);

        pasv_cmd[0] = '\0';
        strcat(pasv_cmd, PASV);
        strcat(pasv_cmd, CRLF);

        if (send_cmd(socket_fd, pasv_cmd, pasv_cmd_size)) {
                fprintf(stderr, "Error sending PASV command\n");
                return EXIT_FAILURE;
        }

        if (read_response(socket_fd, response)) {
                fprintf(stderr, "Error reading server response\n");
                return EXIT_FAILURE;
        }

        if (response->response_code != PASV_SUCCESS) {
                fprintf(stderr,
                        "Error entering passive mode.\n Response: %d - %s\n",
                        response->response_code, response->response);
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

int convert_to_port(char *response, char *ip, int *port)
{
        char *cp = strdup(response);

        char *values = strtok(cp, "(");
        values = strtok(NULL, ")");

        int tmp[6];
        sscanf(values, "%d, %d, %d, %d, %d, %d", &tmp[0], &tmp[1], &tmp[2],
               &tmp[3], &tmp[4], &tmp[5]);

        *port = tmp[4] * 256 + tmp[5];
        sprintf(ip, "%d.%d.%d.%d", tmp[0], tmp[1], tmp[2], tmp[3]);

        return EXIT_SUCCESS;
}

int request_file(int socket_fd, char *file)
{
        int retr_cmd_size = strlen(file) + RETR_CMD_SIZE + CRLF_SIZE + 1;
        char *retr_cmd = malloc(retr_cmd_size);

        retr_cmd[0] = '\0';
        strcat(retr_cmd, RETR);
        strcat(retr_cmd, " ");
        strcat(retr_cmd, file);
        strcat(retr_cmd, CRLF);

        if (send_cmd(socket_fd, retr_cmd, retr_cmd_size)) {
                fprintf(stderr, "Error sending retr command\n");
                return EXIT_FAILURE;
        }

        struct server_response response;
        memset(&response, 0, sizeof(struct server_response));

        if (read_response(socket_fd, &response)) {
                fprintf(stderr, "Error reading server response!\n");
                return EXIT_FAILURE;
        }

        if (response.response_code != RETR_SUCCESS) {
                fprintf(stderr, "Error with retr command.\nResponse: %d - %s\n",
                        response.response_code, response.response);
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}

int logout(int socket_fd)
{
        struct server_response response;
        memset(&response, 0, sizeof(struct server_response));
        int logout_cmd_size = QUIT_CMD_SIZE + CRLF_SIZE;
        char *logout_cmd = malloc(logout_cmd_size);

        logout_cmd[0] = '\0';
        strcat(logout_cmd, QUIT);
        strcat(logout_cmd, CRLF);

        if (send_cmd(socket_fd, logout_cmd, logout_cmd_size)) {
                fprintf(stderr, "Error sending logout command\n");
                return EXIT_FAILURE;
        }

        if (read_response(socket_fd, &response)) {
                fprintf(stderr, "Error reading server response\n");
                return EXIT_FAILURE;
        }

        if (response.response_code != QUIT_SUCCESS) {
                fprintf(stderr, "Error quitting.\n Response: %d - %s\n",
                        response.response_code, response.response);
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}
