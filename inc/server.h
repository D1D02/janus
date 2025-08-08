#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/ip.h>

#define STOP_RECEIVING_DATA 0

int init_server();
void * request_handler( void * );

#endif
