#ifndef RCOM_PARSER_H_
#define RCOM_PARSER_H_

struct url_parser {
        char *user;
        char *password;
        char *host;
        char *host_name;
        char *ip;
        char *path;
};

/**
 * @brief Parses the URL supplied as argument and fills the struct with the
 *        appropriate fields
 *
 * @param parser Struct that holds the relevant fields of the URL
 *
 * @param url URL supplied as argument
 *
 * @return 0 if successfull, 1 otherwise
 *
 */
int parse_url(struct url_parser *parser, char *url);

/**
 * @brief Determines if the url has a user inside
 *
 * @param url URL to determine if it has a user or not
 *
 * @return 1 if TRUE, 0 if FALSE
 */
int url_has_user(char *url);

#endif // RCOM_PARSER_H_
