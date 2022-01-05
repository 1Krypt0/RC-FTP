#include "connection.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int send_cmd(int socket_fd, char *cmd, size_t cmd_size)
{
        if (write(socket_fd, cmd, cmd_size) != cmd_size) {
                fprintf(stderr, "Error writing command!\n");
                return EXIT_FAILURE;
        }

        if (write(socket_fd, CRLF, CRLF_SIZE) != CRLF_SIZE) {
                fprintf(stderr, "Error writing command terminator\n");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}
