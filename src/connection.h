#ifndef RCOM_CONNECTION_H_
#define RCOM_CONNECTION_H_

/**
 * @brief Starts a connection with the port on the IP adress specified
 *
 * @param ip IP address to connect to
 *
 * @param port Port to connect on that IP address
 *
 * @return The socket descriptor if successful, 1 otherwise
 */
int start_connection(char *ip, int port);

#endif // RCOM_CONNECTION_H_
