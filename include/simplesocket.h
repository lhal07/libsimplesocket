#ifndef ITVLOG_H
#define ITVLOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int send_message(char*,int,char*);
int start_server();

#endif //ITVLOG_H
