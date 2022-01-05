#include "parser.h"
#include "connection.h"
#include "communication.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
        int socket_fd = -1;
        struct url_parser url;
        if (parse_url(&url, argv[1])) {
                fprintf(stderr, "Error parsing url\n");
                return EXIT_FAILURE;
        }
        socket_fd = start_connection(url.ip, DEFAULT_FTP_PORT);
        if (socket_fd == EXIT_FAILURE) {
                fprintf(stderr, "Error starting connection\n");
                return EXIT_FAILURE;
        }

        struct server_response response;
        memset(&response, 0, sizeof(struct server_response));

        read_response(socket_fd, &response);

        if (login(socket_fd, url.user, url.password)) {
                fprintf(stderr, "Error logging in\n");
                return EXIT_FAILURE;
        }

        printf("Succesfully logged in!\n");
        memset(&response, 0, sizeof(struct server_response));

        if (enter_passive_mode(socket_fd, &response)) {
                fprintf(stderr, "Error entering passive mode\n");
                return EXIT_FAILURE;
        }

        printf("Succesfully entered passive mode\n");
        printf("Got a response of %s\n", response.response);

        char *ip = malloc(16);
        int *port = malloc(sizeof(int));
        if (convert_to_port(response.response, ip, port)) {
                fprintf(stderr, "Error converting bytes received in response");
                free(ip);
                return EXIT_FAILURE;
        }

        printf("The result IP is %s\n", ip);
        printf("The result port is %d\n", *port);

        close(socket_fd);

        return EXIT_SUCCESS;
}
