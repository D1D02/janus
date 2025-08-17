#include "../inc/server.h"

int init_server() // Create the socket and return socket descriptor
{
    int sd, opt = 1; // SO_REUSEADDR
    struct sockaddr_in address; // Address of the socket
    socklen_t lenght = sizeof( struct sockaddr_in ); // Length of socket address

    // Socket creation with IPv4(AF_INET) and two-way reliable bytes stream(SOCK_STREAM)
    if( ( sd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
        perror( "Socket creation failed.\n" ), exit( EXIT_FAILURE );

    // SOL_SOCKET specify to modify an option at socket level
    // SO_REUSEADDR specify to reuse the same address even if the port is still in use
    if ( setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) ) < 0 ) 
    {
        perror( "Socket option changes failed.\n" );
        shutdown( sd, STOP_RECEIVING_DATA );
        exit( EXIT_FAILURE );
    }

    // Initialization of address
    memset( &address, 0, lenght );		// Initializing memory with zeros
    address.sin_family = AF_INET;               // IPv4 protocol
    address.sin_port = htons( 8080 );           // Port 8080, htons convert number of port in bytes
    address.sin_addr.s_addr = INADDR_ANY;       // Accept connection from all the interfaces on the machine

    // Attach address to the socket
    if ( bind( sd, ( struct sockaddr * ) &address, lenght ) < 0 )
        perror( "Address binding failed.\n" ), exit( EXIT_FAILURE ); //Modify errors

    // Starting to listen on the socket, with max 100 connections pending
    if ( listen( sd, 100 ) < 0 )
        perror( "Listen start failed.\n" ), exit( EXIT_FAILURE );

    return sd;
}

void* request_handler( void * p_client_sd )
{
  printf( "In request handler.\n" );
  char buffer[2048];
  const int client_sd = *( ( int * ) p_client_sd );
  
  recv( client_sd, &buffer, ( size_t ) ( sizeof( buffer ) - 1), 0 );
  printf( "%s\n\n", buffer );
  request_normalization( ( const char * ) &buffer );
  
  char * response = send_example_response();
  printf( "Request handler: %s\n", response );
  send( client_sd, response, ( size_t ) strlen( response ), 0 );
  free( response );
  
  shutdown(client_sd, SHUT_RDWR);
  
  return p_client_sd;
}


