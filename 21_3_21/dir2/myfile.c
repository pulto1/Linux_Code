#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 128

int main()
{
  close(1);
  int fd = open("log.txt", O_WRONLY | O_CREAT, 0644);
  if(fd < 0)
  {
    perror("open error\n");
    return 1;
  }

  printf("hello world..... %d\n", fd);
  fflush(stdout);
  close(fd);


  //char buf[SIZE];
  //read(0, buf, SIZE);
  //write(1, buf, strlen(buf));
 //int fd = open("log.txt", O_RDONLY);
 //if(fd < 0)
 //{
 //  perror("open error!\n");
 //  return 0;
 //}

 //int fd1 = open("log1.txt", O_RDONLY|O_CREAT);
 //int fd2 = open("log2.txt", O_RDONLY|O_CREAT);
 //int fd3 = open("log3.txt", O_RDONLY|O_CREAT);
 //int fd4 = open("log4.txt", O_RDONLY);
 //int fd5 = open("log5.txt", O_RDONLY);
 //
 //char buf[SIZE];
 //read(fd, buf, SIZE);
 //printf("%d: %s\n", fd, buf);
 //
 //printf("%d \n", fd1);
 //printf("%d \n", fd2);
 //printf("%d \n", fd3);
 //printf("%d \n", fd4);
 //printf("%d \n", fd5);

 //close(fd);

  //FILE* fp = fopen("log.txt", "w");
  //if(NULL == fp)
  //{
  //  perror("fopen error!\n");
  //  return 1;
  //}

  //const char* msg = "hello world!\n";
  //fwrite(msg, strlen(msg), 1, stdout);

  //fclose(fp);
  return 0;
}
