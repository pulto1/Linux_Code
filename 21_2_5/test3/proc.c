#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{

  pid_t ret = fork();
  sleep(1);

  if(ret > 0)
  {
    int count = 5;
    while(count--)
    {
       printf("I am parent! pid is: %d\n", getpid());
       sleep(1);
    }
    exit(0);
  }

  else if(ret == 0)
  {
   while(1)
    {
      printf("I am child! pid is: %d ppid is: %d\n", getpid(), getppid());
      sleep(1);
    }
  }

  else
  {

    printf("fork error\n");
  }

  sleep(1);
  return 0;
}
