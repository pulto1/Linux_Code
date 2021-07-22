#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

void* thread_run(void* arg)
{
  while(1)
  {
    printf("I am %s, pid: %d, my thread id is %p\n", (char*)arg, getpid(), pthread_self());
    sleep(1);
  }
}

int main()
{
  pthread_t tid;
  pthread_create(&tid, NULL, thread_run, (void*)"thread 1");

  while(1)
  {
    printf("I am main thread!, pid: %d, my thread id id %p\n", getpid(), pthread_self());
    sleep(2);
  }

  return 0;
}
