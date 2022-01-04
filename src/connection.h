#ifndef RCOM_CONNECTION_H_
#define RCOM_CONNECTION_H_

struct server_response {
        char response[1024];
        int response_code;
};

int start_connection(char *ip, int port);

int read_response(int socket_fd, struct server_response *response);

#endif // RCOM_CONNECTION_H_
