#include "RingQueue.hpp"

//mutex1 mutex2
void* consumer(void* ring_queue)
{
  RingQueue* rq = (RingQueue*)ring_queue;

  while(true)
  {
    sleep(1); //消费者慢
    int data = 0;
    //lock(mutex1);
    rq->Get(data);
    //unlock(mutex1);
    std::cout << "consumer done ... #" << data << std::endl;
  }
}

void* productor(void* ring_queue)
{
  RingQueue* rq = (RingQueue*)ring_queue;

  int count = 100;
  while(true)
  {
    sleep(1); //生产者慢
    //lock(mutex2);
    rq->Put(count);
    //unlock(mutex2);
    count++;
    if(count > 110)
    {
      count = 100;
    }

    std::cout << "productor done ..." << std::endl;
  }
}

int main()
{
  pthread_t c, p;
  RingQueue* rq = new RingQueue();
  pthread_create(&c, nullptr, consumer, rq);
  pthread_create(&p, nullptr, productor, rq);

  pthread_join(c, nullptr);
  pthread_join(p, nullptr);

  delete rq;

  return 0;
}
