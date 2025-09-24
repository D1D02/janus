#include "../inc/response.h"


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
  
  char * response = ( char * ) malloc( 512 * sizeof( char ) );
  
  snprintf( 
    response, ( size_t ) 512, 
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
    if( html == NULL || html->size == 0 )
    {
        response->response_body = bad_request(); 
        return response;
    }
    
    size_t header_len = snprintf(
    	NULL, 0, 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: %zu\r\n"
        "\r\n", 
        html->size
    );

    size_t total_len = header_len + html->size + 1; 
    char * response_body = ( char * ) malloc( total_len );

    if (response_body == NULL) 
    {
        free(path);
        free(html->content);
        free(html);
        response->response_body = bad_request();
        return response;
    }

    snprintf(
    	response_body, total_len,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: %zu\r\n"
        "\r\n"
        "%s",
        html->size, html->content
    );

    response->response_body = response_body;
    printf( "In response, response body: %s\n", response->response_body );
    
    free(path);
    free(html->content);
    free(html);
    
    return response;
}




char * bad_request( void )
{
  printf( "In response sender.\n" );
  const char * response_html =
    "<!DOCTYPE HTML>\n"
    "<html>\n"
    "<body>\n"
    "<h1>Bad request:400</h1>\n"
    "</body>\n"
    "</html>\n";
  
  char * response = ( char * ) malloc( 512 * sizeof( char ) );
  
  snprintf( 
    response, ( size_t ) 512, 
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

