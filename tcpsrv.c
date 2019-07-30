/***************************************/
/*              TCP server             */
/***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <ctype.h>

#define BUFSIZE 1024                      // buffer size
#define PORT_NO 2001                      // port number
#define error(a,b) fprintf(stderr, a, b)  // error 'function'

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

//generált mezők tömbje
int def[17][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                  {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

void gen()
{
   //ürítés
   for(int i=0;i<9;i++) for(int j=0;j<9;j++) t[i][j]=' ';
   //random generálás
   int rossz=1; //1=true 0=false
   srand((unsigned)time(NULL));
   for(int i=0;i<17;i++)
   {
      rossz=1;
      while(rossz==1)
      {
         //generálás
         for(int j=0;j<3;j++) def[i][j]=(rand()%9)+1;

         //feltételek vizsgálata
         rossz=0;
         //az első szám nem ismétlődhet
         if(i==0) rossz=0;
         //ism szűrő
         else
         {
            for(int j=0;j<i;j++)
           {
           if(def[j][0]==def[i][0] && def[j][1]==def[i][1]) {rossz=1;break;}
           }

           //ismétlődik sorban
           for(int j=0;j<i;j++)
           {
           if(def[i][0]==def[j][0] && def[i][2]==def[j][2]) {rossz=1;break;}
           }

           //ismétlődés oszlopban
           for(int j=0;j<i;j++)
           {
           if(def[i][1]==def[j][1] && def[i][2]==def[j][2]) {rossz=1;break;}
           }

           //3x3 négyzetben ismétlődés

           for(int j=0;j<i;j++)
            {
               //tesztelő kiiratás//cout<<i<<" "<<def[i][0]<<" "<<def[j][0]<<" | "<<def[i][1]<<" "<<def[j][1]<<" | "<<def[i][2]<<" "<<def[j][2]<<endl;
               if((def[i][0]-1)/3==(def[j][0]-1)/3 && (def[i][1]-1)/3==(def[j][1]-1)/3 && def[i][2]==def[j][2]) {rossz=1;break;}
            }
         }
      }
   }
//táblázatba rendezés
   for(int i=0;i<17;i++)
      {
      t[def[i][1]-1][def[i][0]-1]=def[i][2]+'0';
      }
}

//a tábla helyességének a tesztelése
int test()
{
   //sor tesztelés
   for(int i=0;i<9;i++)
   {
      int sum=0;
      for(int j=0;j<9;j++)
      {
         sum+=t[i][j];
      }
      if(sum!=45) return i+1;
   }
   //oszlop teszt
   for(int i=0;i<9;i++)
   {
      int sum=0;
      for(int j=0;j<9;j++)
      {
         sum+=t[j][i];
      }
      if(sum!=45) return i+1;
   }
   return 0;
}

int defe(int x,int y)
{
   int a=0;
   for(int i=0;i<17;i++)
   {
      if(def[i][0]==x && def[i][1]==y) {a=1;break;}
   }
   if(a==1) return 1;
   else if(a==0) return 0;
}

int main(int argc, char *argv[] ){ 	// arg count, arg vector 

   /* Declarations */
   int fd;	        	           		// socket endpt
   int fdc[2];                        	// socket endpt
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
   int feladta[2]={0,0};

   /* Initialization */
   on                     = 1;
   flags                  = 0;
   bytes                  = BUFSIZE;
   server_size            = sizeof server;
   client_size            = sizeof client;
   server.sin_family      = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port        = htons(PORT_NO);

void bezar()
{
  /* Closing sockets and quit */
   close(fd);
   exit(0); 
}

   /* Creating socket */
   fd = socket(AF_INET, SOCK_STREAM, 0 );
   if (fd < 0) {
      error("%s: Socket creation error\n",argv[0]);
      exit(1);
      }

   /* Setting socket options */
   setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
   setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

   /* Binding socket */
   err = bind(fd, (struct sockaddr *) &server, server_size);
   if (err < 0) {
      error("%s: Cannot bind to the socket\n",argv[0]);
      exit(2);
      }

   /* Listening */
   err = listen(fd, 10);
   if (err < 0) {
      error("%s: Cannot listen to the socket\n",argv[0]);
      exit(3);
      }

for(int i=0;i<2;i++){
   /* Accepting connection request */
	printf("Waiting for connections...\n");
   fdc[i] = accept(fd, (struct sockaddr *) &client, &client_size);
   if (fdc[i] < 0) {
      error("%s: Cannot accept on socket\n",argv[0]);
      exit(4);
      }
   printf("Player%d connected.\n",i+1);

}

//mind2 player csatlakozva
printf("Both player has joined.\n");

//tábla generálás
gen();
kiir();
//tábla küldése
/*{sprintf(buffer,"tabla");int l=strlen(buffer);
for(int j=0;j<9;j++) for(int k=0;k<9;k++) {buffer[l]=t[j][k]; l++;}
}
bytes=strlen(buffer)+1;
for(int i=0;i<2;i++)
{
   printf("%s\n",buffer );
   trnmsize=send(fdc[i],buffer,bytes,flags);
   if(trnmsize<0){
      error("%s: Cannot send data to the client.\n",argv[0]);
      exit(5);
      }
}
*/

for(;;)
   {

      for(int i=0;i<2;i++)
      {
         ciklus:
         if(feladta[i]!=0) continue;

         /* parancs kérés */
         sprintf(buffer,"mehet");
         bytes = strlen(buffer)+1;
         trnmsize = send(fdc[i], buffer, bytes, flags);
         if (trnmsize < 0) {
            error("%s: Cannot send data to the client.\n",argv[0]);
            exit(6);
            }

               /* Receiving data from the client */
      	printf("Waiting for player%d's message...\n",i+1);
         bytes=BUFSIZE;
         rcvsize = recv( fdc[i], buffer, bytes, flags );
         if (rcvsize < 0) {
            error("%s: Cannot receive from the socket\n",argv[0]);
            exit(7);
            }
            bytes=rcvsize-1;


            /* Beérkezett üzenetet kiírja */
         printf("Player%d: %s \n",i+1 ,buffer);
         //bemenet kezelése
            //feladáskezelés
            if(strcmp(buffer,"feladom")==0) {feladta[i]=1;close(fdc[i]);}

            //kitöltéskezelés
               else  if(strncmp(buffer,"kitolt(",7)==0)  
               {
                  int a=0;
               for(int j=0;j<17;j++)
                  {
                     if(def[i][0]==buffer[8]-'0' && def[i][1]==buffer[10]-'0') 
                        {
                           a=1;break;
                        }
                  }
               if(a==0) {
                        t[buffer[8]-'0'][buffer[10]-'0']=buffer[12];
                        kiir();
                        printf("kitoltotttabla\n");
                        sprintf(buffer,"kitoltotttabla");
                        bytes=strlen(buffer)+1;
                        trnmsize=send(fdc[i],buffer,bytes,flags);
                        if(trnmsize<0){
                           error("%s: Cannot send data to the client.\n",argv[0]);
                           exit(5);
                           }
                        }
               else if(a==1)  
                              {
                                 printf("This spot can't be edited.\n");
                                 sprintf(buffer,"This spot can't be edited.");
                                 bytes=strlen(buffer)+1;
                                 trnmsize=send(fdc[i],buffer,bytes,flags);
                                 if(trnmsize<0){
                                    error("%s: Cannot send data to the client.\n",argv[0]);
                                    exit(5);
                                    }
                              }
               }

            //törléskezelés
               else if(strncmp(buffer,"torol(",6)==0) {
                                                         int a=buffer[6]-'0',b=buffer[8]-'0';
                                                      if(defe(b,a))           {t[buffer[6]-'0'-1][buffer[8]-'0'-1]=' ';kiir();printf("Number deleted.\n");}
                                                         else  {
                                                                  printf("This spot can't be deleted.\n");
                                                                  sprintf(buffer,"This spot can't be deleted.");
                                                                  bytes=strlen(buffer)+1;
                                                                  trnmsize=send(fdc[i],buffer,bytes,flags);
                                                                  if(trnmsize<0){
                                                                     error("%s: Cannot send data to the client.\n",argv[0]);
                                                                     exit(5);
                                                                     }
                                                                     send(fdc[i],"mehet",bytes,flags);
                                                                  goto ciklus;
                                                               }
                                                      }
                     
            //passzoláskezelés
               else if(strcmp(buffer,"passz")==0) {printf("Player%d passed!\n",i+1 );continue;}
            //helytelen input
            else {
               printf("Invalid input.\n");
               sprintf(buffer,"Invalid input.");
               bytes=strlen(buffer)+1;
               trnmsize=send(fdc[i],buffer,bytes,flags);
               if(trnmsize<0){
                  error("%s: Cannot send data to the client.\n",argv[0]);
                  exit(5);
                  }
               goto ciklus;
               }

      }

      //ha mind2 feladta kilép
      if(feladta[0]==1 && feladta[1]==1) {printf("Both players left.\n"); close(fd); return 0;}
   }



   
} 
