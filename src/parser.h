#ifndef RCOM_PARSER_H_
#define RCOM_PARSER_H_

/**
 * A url should have the following syntax:
 *
 * ftp://[<user>:<password>@]<host>/<path>
 *
 * ftp:// -> obligatory
 * [<user>:<password>] -> optional
 * host -> obligatory
 * path -> obligatory
 *
 **/

typedef struct {
        char *user;
        char *password;
        char *host;
        char *path;
} url_parser;

#endif // RCOM_PARSER_H_
