#include "BlockQueue.hpp"

using namespace std;

void* consumer_run(void* arg)
{
  BlockQueue* bq = (BlockQueue*)arg;

  while(true)
  {
    //lock
    Task t;
    bq->Get(t);
    cout << "consumer: " << t.x << "+" << t.y << "=" << t.Run() << endl;
    //unlock
  }
}

void* productor_run(void* arg)
{
  sleep(1);
  BlockQueue* bq = (BlockQueue*)arg;
  //int count = 0;
  while(true)
  {
    //lock
    //count = count % 5 + 1;
    int x = rand() % 10 + 1;
    int y = rand() % 100 + 1;

    Task t(x, y);
    bq->Put(t);
    //unlock
    cout << "productor Task is :" << x << "+" << y  << "= ?" << endl;
    sleep(1);
  }
}

int main()
{
  BlockQueue* bq = new BlockQueue(5);
  pthread_t c, p;
  pthread_create(&c, nullptr, consumer_run, (void*)bq);
  pthread_create(&p, nullptr, productor_run, (void*)bq);

  pthread_join(c, nullptr);
  pthread_join(p, nullptr);
  
  delete bq;
  
  return 0;
}
