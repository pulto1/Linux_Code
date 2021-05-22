#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define SIZE 256
#define NUM 16

int main()
{
  char cmd[SIZE];
  const char* cmd_line = "[tmp@centos7 dir1]";
  while(1)
  {
    cmd[0] = 0;
    printf("%s", cmd_line);
    fgets(cmd, SIZE, stdin);
    cmd[strlen(cmd) - 1] = '\0';
    char* args[NUM];
    args[0] = strtok(cmd, " ");
    int i = 1;
    do{
      args[i] = strtok(NULL, " ");
      if(args[i] == NULL)
      {
        break;
      }
      i++;
    }while(1);

    pid_t id = fork();
    if(id < 0)
    {
      perror("fork error!\n");
      continue;
    }

    if(id == 0)
    {
      //child
      execvp(args[0], args);
      exit(1);
    }

    int status = 0;
    pid_t ret = waitpid(id, &status, 0);
    if(ret > 0)
    {
      printf("status code: %d\n", (status >> 8) & 0xff);
    }
  }
  return 0;
}
