#include "ThreadPool.hpp"

int main()
{
  ThreadPool* tp = new ThreadPool();
  tp->ThreadPoolInit();

  //server
  while(true) //主线程做服务器，不断构造任务，并把任务放到线程池中去执行
  {
    int x = rand() % 10 + 1;
    Task t(x);

    tp->Put(t);
    sleep(1);
  }

  return 0;
}
