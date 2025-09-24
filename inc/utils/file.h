#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HTML_SIZE 10000

typedef struct FILE_CONTENT{
  char * content;
  size_t size;
}file_c;


/*---------------------------------------------------File Handling----------------------------------------------------*/
FILE * open_file_read_only( const char * );
file_c * get_html_data( const char * );

/*-------------------------------------------------String Manipulation------------------------------------------------*/
unsigned short int characters_count( FILE * fptr );

#endif
