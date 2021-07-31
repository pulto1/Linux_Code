#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int a = 10;

void* thread_run(void* arg)
{
  while(1)
  {
    printf("%s, %lu, pid: %d\n", (char*)arg, pthread_self(), getpid());
    printf("%s global variable: %d, %p\n", (char*)arg, a, &a);
    sleep(1);
  }

  return (void*)10;
}

int main()
{
  pthread_t tid;
  pthread_t tid1;
  pthread_create(&tid, NULL, thread_run, "thread 0");
  pthread_create(&tid1, NULL, thread_run, "thread 1");

  printf("main: %lu, pid: %d\n", pthread_self(), getpid());

  printf("before: %s global variable: %d, %p\n", "main", a, &a);
  sleep(10);
  a = 100;
  printf("after: %s gloable variable: %d, %p\n", "main", a, &a);

  void* ret = NULL;
  pthread_join(tid, &ret);
  printf("thread quit code: %lld\n", (long long)ret);

  return 0;
}
