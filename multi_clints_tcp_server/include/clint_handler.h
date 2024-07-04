#ifndef CLINT_HANDLER_H
#define CLINT_HANDLER_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>


#define MAX_CLINT_NUMBER 10
#define BUFFER_SIZE 1024

extern int connectedClinets[MAX_CLINT_NUMBER];
extern int clintCounter;

static void remove_clint(int index);
static int find_clint(int clintfd);
void *podcast_msg(char *msg, int msgLength, int recentClint);
void *clint_handler(void *arg);

#endif // CLINT_HANDLER_H

