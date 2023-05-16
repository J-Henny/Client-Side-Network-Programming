#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

#define WINDOWSIZE 10
#define MAXWAITTIME 1
#define SENDSIZE 3
int sendStuff(char *buffer, int sd, struct sockaddr_in server_address);
char *rtrim(char *s);
int main(int argc, char *argv[])
{
  int sd;
  struct sockaddr_in server_address;
  char buffer[100] = "“Hello, how are you today? I am fine thanks for asking";

  int portNumber;
  char serverIP[29];


  if (argc < 3){
    printf ("usage is client <ipaddr> <portnumber>\n");
    exit(1);
  }

  printf ("you are sending '%s'\n", buffer);

  sd = socket(AF_INET, SOCK_DGRAM, 0);

  portNumber = strtol(argv[2], NULL, 10);
  strcpy(serverIP, argv[1]);

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(portNumber);
  server_address.sin_addr.s_addr = inet_addr(serverIP);
  sendStuff(buffer, sd, server_address);


  return 0 ; 

}

int sendStuff(char *buffer, int sd, struct sockaddr_in server_address){
  int bottomOfWindow, topOfWindow;
  bottomOfWindow = topOfWindow = 0;
  time_t timeSent;
  time_t currentTime;
  int currentFrame;
  int rc;
  int maxWindow = WINDOWSIZE;
  char bufferOut[100];
  struct sockaddr_in fromAddress;
  socklen_t fromLength = sizeof(struct sockaddr_in);
  char bufferRead[100];
  int ackNumber = 0; 
  int totalBytesToSend;
  int bytesLeftToSend;
  int sizeOfSendBuffer = 2;
  int sentWindowSize = 0;
  int dataSize = sizeOfSendBuffer;
  int basePacketSize = 15;

  totalBytesToSend = strlen(buffer); //change this once we add in file IO
  printf ("totalBytesToSend %d\n", totalBytesToSend);
  bytesLeftToSend = totalBytesToSend; 
  // handle sending the filename and filesize differently
  //  sprintf (bufferOut, "%11d",  htons(totalBytesToSend));
  totalBytesToSend = htonl(totalBytesToSend);
  rc = sendto(sd, &totalBytesToSend, sizeof(totalBytesToSend), 0,
	      (struct sockaddr *) &server_address, sizeof(server_address));
  totalBytesToSend = ntohl(totalBytesToSend);
  currentFrame = 0;
  return (0);
}

