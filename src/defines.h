#ifndef RCOM_DEFINES_H_
#define RCOM_DEFINES_H_

#define TRUE 1
#define FALSE 0
#define MAX_BUFSIZE 1024

#define RESPONSE_CODE_SIZE 3
#define DEFAULT_FTP_PORT 21

// Server Codes
#define SERVER_READY 220
#define USERNAME_OK 331
#define LOGIN_SUCCESS 230
#define RETR_SUCCESS 150

#define USER "USER"
#define PASS "PASS"
#define PASV "PASV"
#define RETR "RETR"
#define USER_CMD_SIZE 4
#define PASS_CMD_SIZE 4
#define PASV_CMD_SIZE 4
#define RETR_CMD_SIZE 4

#define DEFAULT_USER "anonymous"
#define DEFAULT_PASSWORD "pass"

#define CRLF "\r\n"
#define CRLF_SIZE 2

#endif // RCOM_DEFINES_H_
