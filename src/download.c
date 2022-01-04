#include "parser.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
        struct url_parser url;
        parse_url(&url, argv[1]);
        return EXIT_SUCCESS;
}
