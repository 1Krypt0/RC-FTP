#include "parser.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
        if (argc != 2) {
                fprintf(stderr,
                        "Usage: ./download ftp://[<user>:<password>@]<host>/<path>");
                return EXIT_FAILURE;
        }

        struct url_parser url;
        if (parse_url(&url, argv[1])) {
                fprintf(stderr, "Error parsing url\n");
                return EXIT_FAILURE;
        }

        if (transfer_file(&url)) {
                fprintf(stderr, "Error transfering file\n");
                return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
}
