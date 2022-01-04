#include "parser.h"
#include "connection.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

        printf("The response is %s \n and the response code is %d\n",
               response.response, response.response_code);

        return EXIT_SUCCESS;
}
