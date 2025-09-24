#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HTML_SIZE 10000

typedef struct FILE_CONTENT{
  char * content;
  size_t size;
  const char * type;
}file_c;


/*---------------------------------------------------File Handling----------------------------------------------------*/
FILE * open_file_read_only( const char * );
file_c * get_data( const char * );

/*----------------------------------------------------Content Type-----------------------------------------------------*/
const char * get_file_extension( const char * );
const char * get_content_type( const char * );


#endif
