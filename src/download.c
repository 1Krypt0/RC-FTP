#include "parser.h"
#include "connection.h"
#include "defines.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
        struct url_parser url;
        parse_url(&url, argv[1]);
        start_connection(url.ip, DEFAULT_FTP_PORT);
        return EXIT_SUCCESS;
}
