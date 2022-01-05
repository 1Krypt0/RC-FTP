#include "connection.h"
#include "defines.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
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
