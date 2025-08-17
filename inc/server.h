#ifndef SERVER_H
#define SERVER_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#include "./request.h"
#include "./response.h"

#define STOP_RECEIVING_DATA 0

int init_server();

void * request_handler( void * );

#endif
