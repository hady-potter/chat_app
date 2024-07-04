#include "clint_handler.h"



static void remove_clint(int index)
{
  for (int i = index; i < clintCounter; i++)
  {
    connectedClinets[i] = connectedClinets[i + 1];
  }
  clintCounter--;
}

static int find_clint(int clintfd)
{
  for (int i = 0; i < clintCounter; i++)
  {
    if (connectedClinets[i] == clintfd)
    {
      return i;
    }
  }
}

// send msg t all clints but sender
void *podcast_msg(char *msg, int msgLength, int recentClint) {

  for (int i = 0; i < clintCounter; i++) {
    if (connectedClinets[i] == recentClint) {
      continue;
    }
    else
    {
      send(connectedClinets[i], msg, msgLength, 0);
    }
  }
}

void *clint_handler(void *arg) {

  int clintfd = *(int *)arg;
  char msg[BUFFER_SIZE];

  int strLen = 0;
  while (strLen = read(clintfd, msg, BUFFER_SIZE)) {
    
    podcast_msg(msg, strLen, clintfd);
  }

  // remove the servied clint from array
  remove_clint(find_clint(clintfd));
  printf("clint %d disconnected\n", clintfd);
  close(clintfd);

  return NULL;
}
