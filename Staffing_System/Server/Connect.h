#ifndef __CONNECT_H_
#define __CONNECT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "Staff.h"

int CreateServer(char const *ipaddr, char const *port);
int WaitConnect(int sockfd, struct sockaddr_in *clientaddr);
void SendMsg(int clientfd, MSG *msg);
int RecvMsg(int clientfd, MSG *msg);

#endif