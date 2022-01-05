#include "file.h"
#include "connection.h"
#include "communication.h"
#include "defines.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int transfer_file(struct url_parser *url)
{
        int socket_fd = -1;
        socket_fd = start_connection(url->ip, DEFAULT_FTP_PORT);
        if (socket_fd == EXIT_FAILURE) {
                fprintf(stderr, "Error starting connection\n");
                return EXIT_FAILURE;
        }

        struct server_response response;
        memset(&response, 0, sizeof(struct server_response));

        read_response(socket_fd, &response);

        if (login(socket_fd, url->user, url->password)) {
                fprintf(stderr, "Error logging in\n");
                return EXIT_FAILURE;
        }

        printf("Succesfully logged in!\n");
        memset(&response, 0, sizeof(struct server_response));

        if (enter_passive_mode(socket_fd, &response)) {
                fprintf(stderr, "Error entering passive mode\n");
                return EXIT_FAILURE;
        }

        char *ip = malloc(16);
        int *port = malloc(sizeof(int));
        if (convert_to_port(response.response, ip, port)) {
                fprintf(stderr,
                        "Error converting bytes received in response\n");
                free(ip);
                free(port);
                return EXIT_FAILURE;
        }

        int data_fd = -1;
        if ((data_fd = start_connection(ip, *port)) == EXIT_FAILURE) {
                fprintf(stderr, "Error connecting to other port\n");
                free(ip);
                free(port);
                return EXIT_FAILURE;
        }

        free(ip);
        free(port);

        if (request_file(socket_fd, url->path)) {
                fprintf(stderr, "Error retrieving file\n");
                return EXIT_FAILURE;
        }

        memset(&response, 0, sizeof(struct server_response));
        if (read_response(socket_fd, &response)) {
                fprintf(stderr, "Error reading response\n");
                return EXIT_FAILURE;
        }

        if (response.response_code != TRANSFER_COMPLETE) {
                fprintf(stderr, "File transfer not complete\n");
                return EXIT_FAILURE;
        }

        // transfer file goes here

        if (logout(socket_fd)) {
                fprintf(stderr, "Error quitting\n");
                return EXIT_FAILURE;
        }

        printf("Succesfully requested file %s from server\n", url->path);

        close(socket_fd);
        close(data_fd);

        return EXIT_SUCCESS;
}
