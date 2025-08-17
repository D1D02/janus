#include "../inc/request.h"

httpRequest * request_normalization ( const char * buffer )
{
  if( buffer == NULL ) return NULL;
    
    
  printf( "In request normalization  %s\n", buffer );
  unsigned short int i = 0;
  while( buffer[i] != '\0' ) 
  {
    unsigned short int offset = 0;
    while( buffer[i+offset] != '\n' && buffer[i+offset] != '\0' && offset < 2048 ) offset++;
    
    printf( "%d\n", offset );
    char * ss = ( char * ) malloc ( sizeof( char ) * offset );
    strncpy( ss, buffer + i, offset );
    
    if( strstr( ss, "GET" ) != NULL )
    {
      printf( "%s\n", ss );
    }
    
    i += offset + 1;
  }
  
  printf( "\n" );
}
