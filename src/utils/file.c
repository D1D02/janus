#include "../../inc/utils/file.h"

size_t get_file_size( FILE *fptr ) 
{
  if (fptr == NULL)  return 0;
    
  fseek(fptr, 0, SEEK_END);
  size_t size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET); 
    
  return size;
}

/*---------------------------------------------------File Handling----------------------------------------------------*/
FILE * open_file_read_only( const char * location )
{
  FILE* fptr;
  printf( "Open location: %s\n", location );
  fptr = fopen( location, "rb" ); 
  printf( "Open file: %p\n", ( void * ) fptr );
    
  return fptr;
}

file_c * get_data( const char * location )
{
  FILE * fptr;
  file_c * file = ( file_c * ) malloc( sizeof( file_c ) );
  if (file == NULL)  return NULL; 
  file->size = 0;
  file->content = NULL;

  printf( "IN file: %s\n", location );
    
  fptr = open_file_read_only( location );
  if( fptr == NULL )
  {
    printf( "File ptr null.\n" );
    return file;
  }
    
  file->type = get_content_type( get_file_extension( location ) );
  printf( "File type: %s\n", file->type );
    
  file->size = get_file_size( fptr );
    
  printf( "File size: %zu\n", file->size );

  if (file->size == 0) 
  {
    fclose(fptr);
    return file;
  }
    
  file->content = ( char * ) malloc( file->size + 1 );
  if( file->content == NULL ) 
  {
    file->size = 0;
        
    fclose(fptr);
    return file;
  }
    
  size_t bytes_read = fread( file->content, 1, file->size, fptr );
    
  if ( bytes_read != file->size ) 
  {
    free(file->content);
    file->content = NULL;
    file->size = 0;
        
    fclose(fptr);
    return file;
  }
    
  file->content[file->size] = '\0';
    
  fclose( fptr );
  return file;
}

/*----------------------------------------------------Content Type-----------------------------------------------------*/
const char * get_file_extension(const char * location) 
{

  const char * dot = strrchr( location, '.' );
    
  if ( !dot || dot == location )  return "";
  
  return dot + 1;
}



const char * get_content_type( const char * file_extension ) 
{
  if( file_extension == NULL ) return NULL;

  if ( strcmp( file_extension, "html" ) == 0 || strcmp( file_extension, "htm" ) == 0 )  return "text/html; charset=UTF-8"; 
      
  if ( strcmp( file_extension, "css" ) == 0 )  return "text/css; charset=UTF-8"; 
       
  if ( strcmp( file_extension, "js" ) == 0 )  return "application/javascript";
        
  if ( strcmp( file_extension, "jpg" ) == 0 || strcmp( file_extension, "jpeg" ) == 0 )  return "image/jpeg";
        
  if ( strcmp( file_extension, "png" ) == 0 )  return "image/png";
        
  if ( strcmp( file_extension, "gif" ) == 0 )  return "image/gif";
        
  if ( strcmp( file_extension, "svg" ) == 0 )  return "image/svg+xml";
        
  return "application/octet-stream";

}

