#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "common.h"

int main()
{
  key_t k = ftok(PATHNAME, PROJ_ID);
  printf("key: %p\n", k);

  int shmid = shmget(k, SIZE, 0);
  if(shmid < 0)
  {
    perror("shmget");
    return 1;
  }

  printf("shmid: %d\n", shmid);

  char* str = (char*)shmat(shmid, NULL, 0);

  char c = 'a';
  for(; c < 'z'; c++)
  {
    str[c - 'a'] = c;
    sleep(5);
  }

  shmdt(str);
  return 0;
}
