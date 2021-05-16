#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  while(1)
  {
  
     pid_t id = fork();

     if(id < 0)
     {
       //error
       perror("fork error!\n");
       return 1;
     }

     else if(id == 0)
     {
       //child
       execl("/usr/bin/ls", "ls", "-al", NULL);
       exit(1);
     }
     
     pid_t ret = waitpid(id, NULL, 0);
     if(ret > 0)
     {
       printf("cmd running done...!\n");
     }
  }

  return 0;
}
