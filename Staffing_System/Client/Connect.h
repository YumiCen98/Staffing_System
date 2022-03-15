#ifndef __CONNECT_H_
#define __CONNECT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "Staff.h"

int ConnectServer(char const *ipaddr, char const *port);
void SendMsg(int sockfd, MSG *msg);
void RecvMsg(int sockfd, MSG *msg);

#endif