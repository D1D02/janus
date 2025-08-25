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

/*
enum RESPONSE_TYPE{
 OK = 200,
*/


httpResponse * get_response( httpRequest * request )
{
  httpResponse * response = ( httpResponse * ) malloc( sizeof( httpResponse ) );
  
  if( strstr( request->path, ".." ) != NULL )
  {
    response->response_body = bad_request();
    return response;
  }
  
  char * path = ( char * ) malloc( strlen( APP_PATH ) + strlen( request->path ) + 1 );
  if( path  == NULL )
  {
    response->response_body = bad_request(); 
    return response;
  } 
  path[0] = '\0';
  strcat( path, APP_PATH) ;
  strcat( path, request->path );
  printf("PATH: %s%s\n", APP_PATH, request->path );
    
    
  file_c * html = get_html_data( ( const char * ) path );
  if( html == NULL )
  {
    response->response_body = bad_request(); //ToDo: 404 status
    return response;
  }
  
  char * response_body = ( char * ) malloc( BUFFER_SIZE * sizeof( char ) );
  
  snprintf( 
    response_body, ( size_t ) BUFFER_SIZE, 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n"
    "Content-Length: %zu\r\n"
    "\r\n"
    "%s"
    "\0",
    html->size,
    html->content
  );	
  
  response->response_body = response_body;
  printf("In response, repsonse body: %s\n", response->response_body  );
  
  return response;
}




char * bad_request( void )
{
  printf( "In response sender.\n" );
  const char *response_html =
    "<!DOCTYPE HTML>\n"
    "<html>\n"
    "<body>\n"
    "<h1>Bad request:400</h1>\n"
    "</body>\n"
    "</html>\n";
  
  char * response = ( char * ) malloc( BUFFER_SIZE * sizeof( char ) );
  
  snprintf( 
    response, ( size_t ) BUFFER_SIZE, 
    "HTTP/1.1 400 BAD REQUEST\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n"
    "Content-Length: %zu\r\n"
    "\r\n"
    "%s"
    "\0",
    strlen( response_html ),
    response_html
  );	
   
  printf("Bad Response: %s\n", response );
  return response;

}

