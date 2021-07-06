#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
  int pipefd[2] = {0};

  pipe(pipefd);

  pid_t id = fork();
  if(id == 0)
  {
    //child write 
    close(pipefd[0]);
    const char* msg = "I am child.....!\n";
    int count = 0;
    while(1)
    {
      write(pipefd[1], msg, strlen(msg));
      printf("CHILD: %d\n", count++);
     //`` if(count == 5)
     //`` {
     //``   close(pipefd[1]);
     //``   break;
     //`` }
    }
    exit(2);
  }

  else 
  {
    //father read 
    close(pipefd[1]);
    char buffer[64];
    int count = 0;
    while(1)
    {
      ssize_t s = read(pipefd[0], buffer, sizeof(buffer) - 1);
      if(s > 0)
      {
        buffer[s] = 0;

        printf("father get message: %s\n", buffer);
        sleep(1);
      }
      
      if(count++ == 5)
      {
        close(pipefd[0]);
        break;
      }
    }
   int status = 0;
   waitpid(id, &status, 0);
   printf("child exit get a sig, sig number: %d\n", status & 0x7F);
  }

  return 0;
}
