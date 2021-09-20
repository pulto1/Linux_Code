#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void SetNonBlock(int fd)
{
  int fl = fcntl(fd, F_GETFL);
  if(fl < 0)
  {
    printf("fcntl error!\n");
  }

  fcntl(fd, F_SETFL, fl | O_NONBLOCK);
}

int main()
{
  char c = 0;
  SetNonBlock(0);
  while(1)
  {
    sleep(1);
    ssize_t s = read(0, &c ,1);
    if(s > 0)
    {
      printf("%c\n ", c);
    }

    else if(s < 0 && errno == EAGAIN)
    {
      printf("read cond not ok!\n");
    }
    else 
    {
      printf("read error\n");
    }
    
    printf("........................");
  }

  return 0;
}
