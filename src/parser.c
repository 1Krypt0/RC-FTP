#include "parser.h"
#include <stdio.h>
#include <string.h>

int parse_url(url_parser *parser, char *url)
{
        char *token;
        char *cp;

        cp = strdup(url);

        if (cp == NULL) {
                fprintf(stderr, "Error copying url");
                return -1;
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

        printf("Info given:\n");
        printf("User: %s\n", parser->user);
        printf("Password: %s\n", parser->password);
        printf("Host: %s\n", parser->host);
        printf("Path: %s\n", parser->path);

        return 0;
}

int url_has_user(char *arguments)
{
        return strchr(arguments, ':') ? 1 : 0;
}

int main(int argc, char **argv)
{
        url_parser url;
        parse_url(&url, argv[1]);
        return 0;
}
