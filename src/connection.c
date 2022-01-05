#include "connection.h"
#include "defines.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int start_connection(char *ip, int port)
{
        int sockfd;
        struct sockaddr_in server_addr;

        memset((char *)&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(ip);
        server_addr.sin_port = htons(port);

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                fprintf(stderr, "Error creating socket!\n");
                return EXIT_FAILURE;
        }

        if (connect(sockfd, (struct sockaddr *)&server_addr,
                    sizeof(server_addr)) < 0) {
                fprintf(stderr, "Error connecting to the given IP!\n");
                return EXIT_FAILURE;
        }

        return sockfd;
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

        while ((size = getline(&buf, &size, socket)) >= 0) {
                strncat(response->response, buf, size - 1);
                response_size += size;

                if (buf[RESPONSE_CODE_SIZE] == ' ') {
                        sscanf(buf, "%d", &response->response_code);
                        break;
                }
        }

        free(buf);
        fclose(socket);

        return response_size;
}
