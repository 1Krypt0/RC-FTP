#ifndef RCOM_FILE_H_
#define RCOM_FILE_H_

#include "parser.h"

/**
 * @brief Reads the file from the open socket and writes into a file with the
 * same name
 *
 * @param socket_fd File descriptor of the open socket
 *
 * @param file_path Absolute path to the file
 *
 * @return 0 if successful , 1 otherwise
 */
int read_file(int socket_fd, char *file_path);

/**
 * @brief Transfers the file from the remove server on to the local machine
 *
 * @param url Struct holding the necessary parameters to determine the host,
 * the IP address, the file path and the user and password, if necessary
 *
 * @return 0 if successful, 1 otherwise
 * */
int transfer_file(struct url_parser *url);

#endif // RCOM_FILE_H_
