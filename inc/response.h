#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./request.h"
#include "./response_code.h"
#include "./utils/file.h"

typedef struct RESPONSE_TYPE{
  char * response_body;
  unsigned short int status;
}httpResponse;

static const char * APP_PATH = "app";

char * send_example_response( void );

httpResponse * get_response( httpRequest * );

char * bad_request( void );

#endif
