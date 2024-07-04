#ifndef TALK_C
#define TACK_C
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define IP "127.0.0.1"
#define PORT 3000

#define NAME_SIZE 256
#define BUFFER_SIZE 1024
extern char name[NAME_SIZE];

void* sendMsg(void *arg);
void* recvMsg(void *arg);

#endif // TALK_C