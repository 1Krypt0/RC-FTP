#ifndef RCOM_FILE_H_
#define RCOM_FILE_H_

#include "parser.h"
int read_file(int socket_fd, char *file_name);

int transfer_file(struct url_parser *url);

#endif // RCOM_FILE_H_
