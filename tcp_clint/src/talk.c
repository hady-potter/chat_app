#include "talk.h"

void *sendMsg(void *arg){
  int fd = *(int *)arg;
  char msg[BUFFER_SIZE] = {0};
  char namedMsg[BUFFER_SIZE + NAME_SIZE + 10] = {0};
  while (1)
  {
    fgets(msg, BUFFER_SIZE, stdin);
    msg[strlen(msg) - 1] = '\0';

    if (strcmp(msg, "quit") == 0)
    {
      printf("you disconnected\n");
      close(fd);
      exit(0);
    }
    else
    {
      sprintf(namedMsg, "[%s]: %s", name, msg);
      write(fd, namedMsg, strlen(namedMsg));
    }
  }
  return NULL;
}


void *recvMsg(void *arg){
  int fd = *(int *)arg;
  char namedMsg[BUFFER_SIZE + NAME_SIZE + 10] = {0};
  int strLen = 0;

  while (1)
  {
    strLen = read(fd, namedMsg, BUFFER_SIZE + NAME_SIZE);
    if (strLen == -1)
    {
      exit(-1);
    }
    else
    {
      namedMsg[strLen] = '\0';
      printf("%s\n", namedMsg);
    }
  }
  return NULL;
}