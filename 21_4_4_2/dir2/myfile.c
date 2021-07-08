#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int count = 0;
void handler(int signo)
{
  printf("%d\n", count);
  exit(1);
}

int main(int argc, char* argv[])
{
  printf("begin ...\n");

  int i = 1 / 0;

  //int* p;
  //*p = 100;

  printf("end...\n");

  //signal(14, handler);
  //alarm(1);
  //while(1)
  //{
  //  count++;
  //}

  //signal(6, handler);
  //while(1)
  //{
  //  sleep(1);
  //  abort();
  //  //raise(2);
  //}

  //if(argc == 3)
  //{
  //  kill(atoi(argv[1]), atoi(argv[2]));
  //}

  //signal(2, handler);
  //while(1)
  //{
  //  printf("I am running...!\n");
  //  sleep(1);
  //}
  return 0;
}
