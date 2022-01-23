#ifndef RCOM_MESSAGES_H_
#define RCOM_MESSAGES_H_

struct server_response {
        char response[1024];
        int response_code;
};

/**
 * @brief Writes a command to a given socket
 *
 * @param socket_fd File descriptor of the socket
 *
 * @param cmd Command to be sent
 *
 * @param cmd_size Size of the command to be sent
 *
 * @return 0 if successful, 1 otherwise
 *
 * @return 0 if successful, 1 otherwise
 */
int send_cmd(int socket_fd, char *cmd, int cmd_size);

/**
 * @brief Reads a response from the server, storing it in a struct
 *
 * @param socket_fd File descriptor of the socket
 *
 * @param response Struct to hold the response and the response code of the server
 *
 * @return 0 if successful, 1 otherwise
 */
int read_response(int socket_fd, struct server_response *response);

/**
 * @brief Authenticates the user into the server, if required. If no user
 * is specified, the function will default to USER: anonymous and PASS: pass
 *
 * @param socket_fd File descriptor of the socket
 *
 * @param user User to log in to the account
 *
 * @param password User's password
 *
 * @return 0 if successful, 1 otherwise
 */
int login(int socket_fd, char *user, char *password);

/**
 * @brief Instructs the server to enter passive mode
 *
 * @param socket_fd File descriptor of the socket
 *
 * @param response Struct that will hold the server response including response
 * code
 *
 * @return 0 if successful, 1 otherwise
 */
int enter_passive_mode(int socket_fd, struct server_response *response);

/**
 * @brief Converts the server response from enter_passive_mode into an IP and
 * port combination
 *
 * @param response Response text received from enter_passive_mode
 *
 * @param ip Buffer to hold the resulting IP calculated from the response
 *
 * @param port Buffer to hold the resulting port calculated from the response
 *
 * @return 0 if successful, 1 otherwise
 */
int convert_to_port(char *response, char *ip, int *port);

/**
 * @brief Requests the file from the remote server
 *
 * @param socket_fd File descriptor of the socket
 *
 * @param file File path (absolute or relative) to request from the server
 *
 * @return 0 if successful, 1 otherwise
 */
int request_file(int socket_fd, char *file);

/**
 * @brief Exits the current session with the server
 *
 * @param socket_fd File descriptor of the socket
 *
 * @return 0 if successful, 1 otherwise
 */
int logout(int socket_fd);

#endif // RCOM_MESSAGES_H_
