#include "../../inc/utils/file.h"

/*---------------------------------------------------File Handling----------------------------------------------------*/
FILE * open_file_read_only( const char * location )
{
  FILE* fptr;

  fptr = fopen( location, "r" );

  return fptr;
}

file_c * get_html_data( const char * location )
{
  FILE * fptr;
  file_c * html = ( file_c * ) malloc( sizeof( file_c ) );
	
  //Counting characters in a file
  if( ( fptr = open_file_read_only( location ) ) == NULL )
  {
    html->size = 0;
    fclose( fptr );
    return html;
  }
  html->size = characters_count( fptr );
  
  //Copying data
  char * html_content = ( char * )  malloc( html->size * sizeof( char ) );
  if( html_content == NULL ) { html->size = 0; return html; }
  fseek( fptr, 0, SEEK_SET );
  fgets( html_content, html->size, fptr );
  html->content = html_content;
  
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


