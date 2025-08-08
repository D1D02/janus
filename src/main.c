#include "../inc/server.h"

int main()
{
  printf( "Server started.\n" );
  int sd = init_server();
  
  int client_sd;
  struct sockaddr_in client_address;
  socklen_t address_lenght = sizeof( struct sockaddr_in );

  pthread_attr_t attr_thread;
  pthread_attr_init( &attr_thread );
  pthread_attr_setdetachstate( &attr_thread, PTHREAD_CREATE_DETACHED );

  while(1)
  {
    if( ( client_sd = accept( sd, ( struct sockaddr * ) &client_address, &address_lenght ) ) < 0 )
    {
      perror( "Client request not accepted.\n" );
      continue;
    }

    pthread_t tid;

    if( pthread_create( &tid, &attr_thread, request_handler, &client_sd ) != 0 )
    {
      perror( "Error in the thread creation.\n" );
      continue;
    }
  }
	
  return 0;
}

