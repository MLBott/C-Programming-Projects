/* myloggerd.c
 * Source file for thread-lab
 * Creates a server to log messages sent from various connections
 * in real time.
 *
 * Student: Michael Bottom
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <pthread.h>
#include "message-lib.h"

// forward declarations
int usage( char name[] );
// a function to be executed by each thread
void * recv_log_msgs( void * arg );

// globals
int read_size;
int log_fd; 
int clientfd;
char client_message[4000];

void * recv_log_msgs( void * arg ) {
	int clientfd = *((int *)arg);

	while(read_msg(clientfd, client_message, 256) > 0) {
		write(log_fd, client_message, strlen(client_message));
	}
	close(clientfd);
	return NULL;
}

int error_msg( char * msg ) 
{
	printf( "%s\n", msg );
	return -1;
}

int usage( char name[] )
{
	printf( "Usage:\n" );
	printf( "\t%s <log-file-name> <UDS path>\n", name );
	return -1;
}

int main( int argc, char * argv[] )
{
	if ( argc != 3 )
		return usage( argv[0] );

	// open the log for appending
	log_fd = open(argv[1], O_RDWR | O_APPEND | O_CREAT,0777);

	if(log_fd == -1) {
		error_msg("No such file");
		return error_msg(argv[1]);
	}

	// permit message connections
	int listener = permit_connections(argv[2]); 
		if(listener == -1) {
			return -1;
		}

	pthread_t client_thread;

	// loop to accept message connections;
	// as each connection is accepted,
	// launch a new thread that calls
	// recv_log_msgs(), which receives
	// messages and writes them to the log file
	// when accept_next_connection returns -1, terminate the loop	
	while(1) {
		if((intptr_t)accept_next_connection == -1) {
			break;
		}
		printf("Attemping connection on path %s..\n", argv[2]);
		int * clientfdp = malloc(sizeof(int));
		*clientfdp = accept_next_connection(listener);
		printf("Listener acquired\n");	
		pthread_create(&client_thread, NULL, recv_log_msgs, clientfdp);
	}
		
	// close the listener
	close_listener(listener);
	// close the log file
	close(log_fd);

	return 0;
}
