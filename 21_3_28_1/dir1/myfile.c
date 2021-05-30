#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main()
{
  // close(1);
  int fd = open("log.txt", O_CREAT | O_WRONLY, 0644);
  if(fd < 0)
  {
    perror("open error");
    return 1;
  }
 
  dup2(fd, 1);
  close(fd);
  const char* str = "hello world: write!\n";
  const char* str1 = "hello world: printf\n";
  const char* str2 = "hello world: fprintf\n";
  write(1, str, strlen(str));
  printf(str1);
  fprintf(stdout, str2);

  // fork();

  fflush(stdout);
  return 0;
}
