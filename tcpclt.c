/***************************************/
/*             TCP client              */
/***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFSIZE 1024
#define PORT_NO 2001
#define error(a,b) fprintf(stderr, a, b)

char t[9][9]={ {' ',' ',' ',' ',' ',' ',' ',' ',' '},
               {' ',' ',' ',' ',' ',' ',' ',' ',' '},
               {' ',' ',' ',' ',' ',' ',' ',' ',' '},
               {' ',' ',' ',' ',' ',' ',' ',' ',' '},
               {' ',' ',' ',' ',' ',' ',' ',' ',' '},
               {' ',' ',' ',' ',' ',' ',' ',' ',' '},
               {' ',' ',' ',' ',' ',' ',' ',' ',' '},
               {' ',' ',' ',' ',' ',' ',' ',' ',' '},
               {' ',' ',' ',' ',' ',' ',' ',' ',' '}};

void kiir()
{
printf("     ");
for(int a=0;a<9;a++) {printf("%d   ",a+1);}
   printf("\n   -------------------------------------\n");
for(int i=0;i<9;i++)
   {
      printf("%d  |",i+1);
      for(int j=0;j<9;j++) {printf(" %c |",t[i][j] );}
         printf("\n   -------------------------------------\n");
   }
}

void tabla(char* b)
{
   int k=5;
   for(int i=0;i<9;i++)
   {
      for(int j=0;j<9;j++)
      {
         t[i][j]=b[k];
         k++;
      }
   }
}

/*int startwith(char* s,char* b)
{
   int a=1;
            for(int i=0;i<strlen(s);i++)
               {if(b[i]!=s[i]) {a=0;break;}}
            if(a==1) return 0;
            else if(a==0) return 1;
}
*/
int main(int argc, char *argv[] ) {// arg count, arg vector   

   /* Declarations */
   int fd;	                       // socket endpt	
   int flags;                      // rcv flags
   struct sockaddr_in server;	     // socket name (addr) of server 
   struct sockaddr_in client;	     // socket name of client 
   int server_size;                // length of the socket addr. server 
   int client_size;                // length of the socket addr. client 
   int bytes;    	                 // length of buffer 
   int rcvsize;                    // received bytes
   int trnmsize;                   // transmitted bytes
   int err;                   	// error code
   int ip;			// ip address
   char on;                        // 
   char buffer[BUFSIZE+1];         // datagram dat buffer area
   char server_addr[16];           // server address	

void bezaras()
{
close(fd);
exit(0);
}

   /* Initialization */
   on    = 1;
   flags = 0;
   server_size = sizeof server;
   client_size = sizeof client;
   sprintf(server_addr, "%s", argv[1]);
   ip = inet_addr(server_addr);
   server.sin_family      = AF_INET;
   server.sin_addr.s_addr = ip;
   server.sin_port        = htons(PORT_NO);
   
   

   /* Creating socket */
   fd = socket(AF_INET, SOCK_STREAM, 0);
   if (fd < 0) {
      error("%s: Socket creation error.\n",argv[0]);
      exit(1);
   }

   /* Setting socket options */
   setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
   setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

   /* Connecting to the server */
   err = connect(fd, (struct sockaddr *) &server, server_size);
   if (err < 0) {
      error("%s: Cannot connect to the server.\n", argv[0]);
      exit(2);
   }
	
for(;;)
   {

	bytes=BUFSIZE;
	/* recieve  */
   printf("Wait...\n");
   	rcvsize = recv( fd, buffer, bytes, flags );
      bytes=rcvsize-1;
   	if (rcvsize < 0) {
      	error("%s: Cannot receive data from the socket.\n", 		argv[0]);
      	exit(4);
	                    }
printf("%s\n",buffer );
//ha parancsot kér a server
if (strcmp(buffer,"mehet")==0)
               {
                  printf("Your turn!\n");
                  /* Üzenet bekérése */
                  printf("Message: ");
                  scanf("%s",buffer);
                  bytes = strlen(buffer)+1;

                  /* Sending data to the server */
                  trnmsize = send(fd, buffer, bytes, flags);
                  if (trnmsize < 0) {
                     error("%s: Cannot send data to server.\n", argv[0]);
                     exit(3);
                     }
                  if((strcmp(buffer, "feladom"))==0) {printf("Feladtad.\n"); bezaras();}
               }
//ha táblát küld a server
else  if(strncmp(buffer,"tabla",5)==0) {printf("tablajött\n");tabla(buffer);kiir;}
      
//ha invalid az input
else  if(strcmp(buffer,"Invalid input.")==0) printf("%s\n",buffer );


   }

   
} 
