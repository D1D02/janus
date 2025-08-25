#include "../inc/request.h"

httpRequest * request_normalization ( const char * buffer )
{
  if( buffer == NULL ) return NULL;
  httpRequest * request = ( httpRequest * ) malloc( sizeof( httpRequest ) );   
 
  unsigned short int i = 0;
  char * ss;
  while( buffer[i] != '\0' ) 
  {
    unsigned short int offset = 0;
    while( buffer[i+offset] != '\n' && buffer[i+offset] != '\0' && offset < 2048 ) offset++;
    
    printf( "%d\n", offset );
    ss = ( char * ) malloc ( sizeof( char ) * offset );
    strncpy( ss, buffer + i, offset );
    
    if( strstr( ss, "GET" ) != NULL )
    {
      printf("SS: %s\n", ss );
      request->method = "GET";
      request->path = extract_path_get_request( ss );
      printf( "GET REQUEST PATH: %s\n", request->path );
    }
    
    i += offset + 1;
    free( ss );
  }
  
  printf( "\n" );
  return request;
}

char * extract_path_get_request( const char * get_request )
{
  char * buffer = ( char * ) malloc( 256 * sizeof( char ) );
  if (buffer == NULL) return NULL;
  
  unsigned short int i = 4;
  unsigned short int j = 0;
    
  while ( get_request[i] != ' ' && get_request[i] != '\0' ) 
  {
    buffer[j] = get_request[i];
    i++;
    j++;
  }
    
  buffer[j] = '\0'; 

  printf( "Path extracted: %s\n", buffer );
  return buffer;
}






