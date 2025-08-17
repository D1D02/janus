#include "../inc/response.h"

#define BUFFER_SIZE 512

char * send_example_response( void )
{
  printf( "In response sender.\n" );
  const char *response_html =
    "<!DOCTYPE HTML>\n"
    "<html>\n"
    "<body>\n"
    "<h1>First Janus Response</h1>\n"
    "</body>\n"
    "</html>\n";
  
  char * response = ( char * ) malloc( BUFFER_SIZE * sizeof( char ) );
  
  snprintf( 
    response, ( size_t ) BUFFER_SIZE, 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n"
    "Content-Length: %zu\r\n"
    "\r\n"
    "%s"
    "\0",
    strlen( response_html ),
    response_html
  );	
  printf( "Size of response: %d\n", strlen( response ) );
    
  return response;

}
