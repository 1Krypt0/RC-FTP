#ifndef RCOM_CONNECTION_H_
#define RCOM_CONNECTION_H_

int start_connection(char *ip, int port);

int close_connection(int socket_fd);

#endif // RCOM_CONNECTION_H_
