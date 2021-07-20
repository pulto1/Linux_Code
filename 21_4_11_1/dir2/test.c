#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void show_pending(sigset_t * pending)
{
  int sig = 1;
  for(; sig <= 31; sig++)
  {
    if(sigismember(pending, sig))
    {
      printf("1");
    }

    else 
    {
      printf("0");
    }
  }

  printf("\n");
}

void handler(int sig)
{
  printf("get a sig: %d\n", sig);
}

int main()
{
  struct sigaction act, oact;

  act.sa_handler = handler;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);

  sigaction(2, &act, &oact);

  while(1)
  {
    sleep(1);
  }

  //signal(2, handler) ;// 捕捉二号信号

  //sigset_t pending;

  //sigset_t block, oblock;
  //sigemptyset(&block);
  //sigemptyset(&oblock);

  //sigaddset(&block, 2);

  //sigprocmask(SIG_SETMASK, &block, &oblock); //阻塞二号信号

  //int count = 0;
  //while(1)
  //{
  //  sigemptyset(&pending);
  //  sigpending(&pending); //取出进程的pending位图
  //  show_pending(&pending);
  //  sleep(1);
  //  count++;

  //  if(count == 20)
  //  {
  //    printf("recover sig mask!\n");
  //    sigprocmask(SIG_SETMASK, &oblock, NULL); //取消二号信号的阻塞状态
  //  }
  //}
  return 0;
}
