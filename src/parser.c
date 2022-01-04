#include "parser.h"
#include "defines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int parse_url(struct url_parser *parser, char *url)
{
        char *token;
        char *cp;

        cp = strdup(url);

        if (cp == NULL) {
                fprintf(stderr, "Error copying url");
                return EXIT_FAILURE;
        }

        //Protocl of the URL
        token = strtok(cp, "/");

        if (strcmp(token, "ftp:")) {
                fprintf(stderr,
                        "Invalid Protocl. The correct Protocol format is ftp://\n");
        }

        // Possibly the user and password, and the host
        token = strtok(NULL, "/");

        parser->path = strtok(NULL, "");

        if (url_has_user(token)) {
                parser->user = strtok(token, ":");
                parser->password = strtok(NULL, "@");
                parser->host = strtok(NULL, "");
        } else {
                parser->user = NULL;
                parser->password = NULL;
                parser->host = token;
        }

        struct hostent *h;

        if ((h = gethostbyname(parser->host)) == NULL) {
                herror("gethostbyname()");
                return EXIT_FAILURE;
        }

        parser->host_name = h->h_name;
        parser->ip = inet_ntoa(*((struct in_addr *)h->h_addr));

        printf("Info given:\n");
        printf("User: %s\n", parser->user);
        printf("Password: %s\n", parser->password);
        printf("Host: %s\n", parser->host);
        printf("Path: %s\n", parser->path);
        printf("Host name  : %s\n", parser->host_name);
        printf("IP Address : %s\n", parser->ip);

        return EXIT_SUCCESS;
}

int url_has_user(char *url)
{
        return strchr(url, ':') ? TRUE : FALSE;
}
