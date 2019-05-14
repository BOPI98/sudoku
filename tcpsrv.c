/***************************************/
/*              TCP server             */
/***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <unistd.h>

#define BUFSIZE 1024                      // buffer size
#define PORT_NO 2001                      // port number
#define error(a,b) fprintf(stderr, a, b)  // error 'function'

int main(int argc, char *argv[] ){ 	// arg count, arg vector 

   /* Declarations */
   int fd;	        	           		// socket endpt
   int fdc;                        	// socket endpt
   int flags;                      	// rcv flags
   struct sockaddr_in server;      	// socket name (addr) of server
   struct sockaddr_in client;	     	// socket name of client
   int server_size;                	// length of the socket addr. server
   int client_size;                	// length of the socket addr. client
   int bytes;		           					// length of buffer 
   int rcvsize;                    	// received bytes
   int trnmsize;                   	// transmitted bytes
   int err;                        	// error code
   char on;                        	// 
   char buffer[BUFSIZE+1];	     		// datagram dat buffer area   

   /* Initialization */
   on                     = 1;
   flags                  = 0;
   bytes                  = BUFSIZE;
   server_size            = sizeof server;
   client_size            = sizeof client;
   server.sin_family      = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port        = htons(PORT_NO);

   /* Creating socket */
   fd = socket(AF_INET, SOCK_STREAM, 0 );
   if (fd < 0) {
      error("%s: Socket creation error\n",argv[0]);
      exit(1);
      }
printf("socket megvan\n");
   /* Setting socket options */
   setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
   setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

   /* Binding socket */
   err = bind(fd, (struct sockaddr *) &server, server_size);
   if (err < 0) {
      error("%s: Cannot bind to the socket\n",argv[0]);
      exit(2);
      }
printf("binding megvolt\n");
   /* Listening */
   err = listen(fd, 10);
   if (err < 0) {
      error("%s: Cannot listen to the socket\n",argv[0]);
      exit(3);
      }
printf("listen\n");


   /* Accepting connection request */
   fdc = accept(fd, (struct sockaddr *) &client, &client_size);
   if (fdc < 0) {
      error("%s: Cannot accept on socket\n",argv[0]);
      exit(4);
      }
printf("accept\n");
   /* Receiving data from the client */
   rcvsize = recv( fdc, buffer, bytes, flags );
   if (rcvsize < 0) {
      error("%s: Cannot receive from the socket\n",argv[0]);
      exit(5);
      }

   /* User interface */
   printf("%i bytes have been received from client.\n Message: %s \n", 
           rcvsize-1, buffer);

   /* Sending acknowledgement to the client */
   sprintf(buffer,"Transmit is OK.");
   bytes = strlen(buffer) + 1;
   trnmsize = send(fdc, buffer, bytes, flags);
   if (trnmsize < 0) {
      error("%s: Cannot send data to the client.\n",argv[0]);
      exit(6);
      }

   /* User interface */
   printf ("Acknowledgement has been sent to the client.\n");

   /* Closing sockets and quit */
   close(fdc);
   close(fd);
   exit(0);
} 
