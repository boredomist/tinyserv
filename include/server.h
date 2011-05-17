#pragma once

#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PAGE_CSS \
  "a.title { color: black; font-size: 24pt; font-family: sans-serif; }\n" \
  "a { color: white; text-decoration: none;}\n"                     \
  "a:hover {font-weight: bold;}\n"                                  \
  ".container {width: 300px; background: #555; padding:10px;"       \
  "border: 2px solid black; opacity: 0.6; border-radius: 10px;}\n"

#define MAX_CONNECTIONS 10
#define BUF_SIZE 0x1000

#define SERVER_FIELD "Server: tinyserv " __DATE__ "\n"

#define BAD_REQUEST_MSG "<!doctype html><html><body><h1>BAD REQUEST</h1></body></html>"

#define bad_request(c) send_client(c, 400, "Bad Request", "text/html", \
                                   strlen(BAD_REQUEST_MSG), BAD_REQUEST_MSG)

typedef struct server {
  int port;
  int sockfd;

  struct sockaddr_in addr;

  char* directory;
} server_t;

server_t* init_server(char* directory, int port);
void deinit_server(server_t* serv);

int run_server(server_t* serv);

void handle_request(server_t* serv, int sockfd, char* req);

void handle_client(server_t* serv, int sockfd);
void send_client(int sockfd, int resp_num, char* resp_msg, char* type, int len, char* cont);

char* get_mime_type(char* filename);

#endif /* _SERVER_H_ */
