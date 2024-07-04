#include <stdio.h> // printf
#include <sys/types.h> // socket, send, recv
#include <sys/socket.h> //socket, send, recv
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h> // inet_addr
#include <stdlib.h> // exit
#include <string.h> // memset
#include <unistd.h> // close
#include <pthread.h>
#include <string.h>


#include "talk.h"

char name[NAME_SIZE];

int main() {

  pthread_t sendThread;
  pthread_t recvThread;
  // 1) create socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd == -1) {
    perror("can NOT create socket!\n");
    exit(1);
  }


  // 2) connect to some server
  struct sockaddr_in sockAddress;

  memset(&sockAddress, 0, sizeof(sockAddress));
  sockAddress.sin_family = AF_INET;
  sockAddress.sin_addr.s_addr = inet_addr(IP);
  sockAddress.sin_port = htons(PORT);

  if (connect(sockfd, (struct sockaddr *)&sockAddress, sizeof(sockAddress)) != 0)
  {
    printf("can NOT connect with -> [%s:%d]\n", IP, PORT);
    exit(2);
  } 
  else {
    printf("======== Welcome to our chatting room ========\n");
    printf("Name> ");
    fgets(name, NAME_SIZE, stdin);
    name[strlen(name) - 1] = '\0';

    pthread_create(&sendThread, NULL, &sendMsg, (void*)&sockfd);
    pthread_create(&recvThread, NULL, &recvMsg, (void*)&sockfd);

  }
  pthread_join(sendThread, NULL);
  pthread_join(recvThread, NULL);

  close(sockfd);
  return 0;

}