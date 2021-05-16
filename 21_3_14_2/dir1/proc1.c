#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
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
    int count = 0;
    while(count < 10)
    {
      printf("child[%d] is running\n", getpid());
      sleep(1);
      count++;
    }
    //int x = 1 / 0;
    exit(12); //子进程退出码为0
  }

  //father
  

  printf("father wait before!\n");
  int st = 0;

  do
  {
    pid_t ret = waitpid(id, &st, WNOHANG);
   if(ret == 0)
   {
     sleep(1);
     printf("child is not quit, check later!\n");
     continue;
   }

   else if(ret > 0)
   {

      if(WIFEXITED(st))
      {
        printf("exit code: %d\n", WEXITSTATUS(st));
      }

      else 
      {
        printf("exit error\n");
      }
      break;
    }
    //if(ret > 0)
    //{
    //  printf("wait success!\n");
    //  printf("st: %d\n", st); //等待成功，打印退出信息
    //  if(st & 0x7f)
    //  {
    //    printf("child running error, exit signal: %d\n", st & 0x7F); // 退出失败，打印退出信号
    //  }

    //  else 
    //  {
    //    int code =((st >> 8) & 0xFF);
    //    if(code)
    //    {
    //      printf("child running success, but result is not right, exit code: %d\n", (st >> 8) & 0xFF); //退出成功，但结果不对，打印退出码
    //    }

    //    else 
    //    {
    //      printf("child running success,  result is  right, exit code: %d\n", (st >> 8) & 0xFF); //退出成功，结果对，退出码为0
    //    }
    //  }
    //}

  else
  {
    printf("wait failed!\n");
    break;
  }

  }while(1);
  printf("father wait after!\n");
  return 0;
}
