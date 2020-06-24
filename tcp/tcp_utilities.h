#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef TCP_UTILITIES_H
#define TCP_UTILITIES_H

#define PORT 8001

char BUFFER[256];

void error(const char *msg);

#endif
