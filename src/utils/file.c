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
    file_c * html = ( file_c * ) malloc( sizeof( file_c ) );
    if (html == NULL)  return NULL; 
    html->size = 0;
    html->content = NULL;

    printf( "IN file: %s\n", location );
    
    fptr = open_file_read_only( location );
    if( fptr == NULL )
    {
        printf( "File ptr null.\n" );
        return html;
    }
    
    html->size = get_file_size( fptr );
    
    printf( "File size: %zu\n", html->size );

    if (html->size == 0) {
        fclose(fptr);
        return html;
    }
    
    html->content = ( char * ) malloc( html->size + 1 );
    if( html->content == NULL ) {
        html->size = 0;
        fclose(fptr);
        return html;
    }
    
    size_t bytes_read = fread( html->content, 1, html->size, fptr );
    
    if (bytes_read != html->size) 
    {
        free(html->content);
        html->content = NULL;
        html->size = 0;
        fclose(fptr);
        return html;
    }
    
    html->content[html->size] = '\0';
    
    fclose( fptr );
    return html;
}


