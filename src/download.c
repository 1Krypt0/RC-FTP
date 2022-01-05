#include "parser.h"
#include "connection.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
        int socket_fd = -1;
        struct url_parser url;
        parse_url(&url, argv[1]);
        socket_fd = start_connection(url.ip, DEFAULT_FTP_PORT);
        if (socket_fd == EXIT_FAILURE) {
                fprintf(stderr, "Error starting connection\n");
                return EXIT_FAILURE;
        }

        struct server_response response;
        memset(&response, 0, sizeof(struct server_response));

        read_response(socket_fd, &response);

        printf("The socket is %d\n", socket_fd);

        printf("The response is %s \n and the response code is %d\n",
               response.response, response.response_code);

        if (login(socket_fd, url.user, url.password)) {
                fprintf(stderr, "Error logging in\n");
                return EXIT_FAILURE;
        }

        close(socket_fd);

        return EXIT_SUCCESS;
}
