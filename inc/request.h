#ifndef REQUEST_H
#define REQUEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HttpRequest{
  char * method;
  char * host;
  char * user_agent;
  char * accept;
  char * content_type;
  unsigned short int content_length;
  char * body;
}httpRequest;

httpRequest * request_normalization ( const char * );

#endif
