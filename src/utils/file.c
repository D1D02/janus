#include "../../inc/utils/file.h"

/*---------------------------------------------------File Handling----------------------------------------------------*/
FILE * open_file_read_only( const char * location )
{
  FILE* fptr;
  printf("Open location: %s\n", location );
  fptr = fopen( location, "r" );
  printf("Open file: %p\n", ( void * ) fptr);

  return fptr;
}

file_c * get_html_data( const char * location )
{
  FILE * fptr;
  file_c * html = ( file_c * ) malloc( sizeof( file_c ) );
  html->size = 0;
  printf("IN file: %s\n", location);
	
  //Counting characters in a file
  fptr = open_file_read_only( location );
  if( fptr == NULL )
  {
    printf("File ptr null.\n");
    return html;
  }
  
  html->size = characters_count( fptr );
  fseek( fptr, 0, SEEK_SET );
  
  //Copying data
  char * html_content = ( char * )  malloc( ( html->size + 1 ) * sizeof( char ) );
  if( html_content == NULL ) { html->size = 0; return html; }
  size_t bytes_read = fread( html_content, 1, html->size, fptr );
  printf( "File size: %u\n", bytes_read );
  html_content[bytes_read] = '\0';
  html->content = html_content;
  printf( "File content: %s\n", html_content );
  
  
  return html;
}


/*-------------------------------------------------String Manipulation------------------------------------------------*/
unsigned short int characters_count( FILE * fptr )
{
  unsigned short int size = 0;

  do
  {
  
    fgetc( fptr );
    size++;
  
  }while( feof( fptr ) == 0 && size < MAX_HTML_SIZE );
  
  return size;
  
}


