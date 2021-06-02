#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#define SIZE 256
#define NUM 16

void redirect(char* cmd)
{
  int fd = -1;
  int redirect_count = 0;
  char* ptr = cmd;
  char* file = NULL;
  while(*ptr)
  {
    if(*ptr == '>')
    {
      *ptr++ = '\0';
      redirect_count++;
      if(*ptr == '>')
      {
        *ptr++ = '\0';
        redirect_count++;
      }

      while(*ptr != '\0' && isspace(*ptr))
      {
        ptr++;
      }

      file = ptr;
      while(*ptr != '\0' && !isspace(*ptr))
      {
        ptr++;
      }
      *ptr = '\0';

      if(1 == redirect_count)
      {
        fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
      }

      else if(2 == redirect_count)
      {
        fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
      }

      dup2(fd, 1);
      close(fd);
    }

    ptr++;
  } 
}

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


    pid_t id = fork();
    if(id < 0)
    {
      perror("fork error!\n");
      continue;
    }

    if(id == 0)
    {
      //child
      redirect(cmd);
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
