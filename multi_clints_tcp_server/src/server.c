#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "clint_handler.h"

#define PORT 3000
int connectedClinets[MAX_CLINT_NUMBER];
int clintCounter = 0;


int main(){

  // 1) create socket
  int serverfd = socket(AF_INET, SOCK_STREAM, 0);
  if(serverfd == -1) {
    printf("Error with creating a socket.\n");
    return 1;
  }
  // setsockopt
  int option = 1;
  if(setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, (void*)&option, (socklen_t)sizeof(option)) == -1) {
    perror("error in setsockopt\n");
    return 9;
  
  }
  // 2) bind socket
  struct sockaddr_in sockAddress;
  memset(&sockAddress, 0, sizeof(sockAddress));
  sockAddress.sin_family = AF_INET;
  sockAddress.sin_addr.s_addr = INADDR_ANY;
  sockAddress.sin_port = htons(PORT);

  if (bind(serverfd, (struct sockaddr*)&sockAddress, sizeof(sockAddress)) == -1) {
    perror("bind faild");
    close(serverfd);
    return 2;
  }
  // 3) listen
  if(listen(serverfd, 5) == -1) {
    perror("can NOT listen.\n");
    close(serverfd);
    return 3;
  }
  printf("Server up & running on port %d...\n", PORT);


  // 4) accept
  int clintfd = 0;
  pthread_t t1;
  while (1)
  {
    socklen_t clintAddressLength;
    struct sockaddr_in clindAddress;
    memset(&clindAddress, 0, sizeof(clindAddress));

    clintfd = accept(serverfd, (struct sockaddr *)&clindAddress, &clintAddressLength);

    if (clintfd == -1) {
      perror("can not accept a request.\n");
      close(clintfd);
      return 4;
    }
    else {
      connectedClinets[clintCounter++] = clintfd;
      pthread_create(&t1, NULL, &clint_handler, (void *)&clintfd);
      pthread_detach(t1);

      printf("new clint with ip [%s:%d] get connected.\n", inet_ntoa(clindAddress.sin_addr), (int)ntohs(clindAddress.sin_port));
    }
  }
  close(serverfd);
  return 0;
  
}