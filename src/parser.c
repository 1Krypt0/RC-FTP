#include "parser.h"
#include <stdio.h>
#include <string.h>

int parse_url(url_parser *parser, char *url)
{
        char *head;
        char *cp;
        cp = strdup(url);
        if (cp == NULL) {
                fprintf(stderr, "Error copying url");
                return -1;
        }
        head = strtok(cp, "/:@");
        printf("The head will be: %s", head);
        return 0;
}
