#ifndef _QUEUE_BLOCK_H_
#define _QUEUE_BLOCK_H_ 

#include <iostream>
#include <pthread.h>
#include <queue>
#include <unistd.h>

class Task
{
  public:
    int x;
    int y;

  public:
    Task(int _x, int _y)
      :x(_x)
       ,y(_y)
    {}

    Task()
    {}

    int Run()
    {
      return x + y;
    }

    ~Task()
    {}
};


class BlockQueue
{
  private:
    std::queue<Task> q;
    size_t cap;
    pthread_mutex_t lock;
    pthread_cond_t c_cond; //将来消费者，在该条件变量下等！
    pthread_cond_t p_cond; //将来生产者，在该条件变量下等！

  public:
    bool IsFull()
    {
      return q.size() >= cap;
    }

    bool IsEmpty()
    {
      return q.empty();
    }

    void LockQueue()
    {
      pthread_mutex_lock(&lock);
    }

    void UnlockQueue()
    {
      pthread_mutex_unlock(&lock);
    }

    void WakeUpComsumer()
    {
      std::cout << "wake up consumer ..." << std::endl;
      pthread_cond_signal(&c_cond);
    }

    void WakeUpProdoctor()
    {
      std::cout << "wake up product ..." << std::endl;
      pthread_cond_signal(&p_cond);
    }

    void ProductWait()
    {
      std::cout << "productor wait ..." << std::endl;
      pthread_cond_wait(&p_cond, &lock);
    }

    void ComsumerWait()
    {
      std::cout << "consumer wait ..." << std::endl;
      pthread_cond_wait(&c_cond, &lock);
    }

  public:
    BlockQueue(size_t _cap)
      :cap(_cap)
    {
      pthread_mutex_init(&lock, nullptr);
      pthread_cond_init(&c_cond, nullptr);
      pthread_cond_init(&p_cond, nullptr);
      
    }

    void Put(Task t)
    {
      LockQueue();
      while(IsFull())
      {
        WakeUpComsumer();
        ProductWait();
      }

      q.push(t);
      UnlockQueue();
    }

    void Get(Task &t)
    {
      LockQueue();
      while(IsEmpty())
      {
        WakeUpProdoctor();
        ComsumerWait();
      }

      t = q.front();
      q.pop();
      UnlockQueue();
    }

    ~BlockQueue()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&p_cond);
      pthread_cond_destroy(&c_cond);
    }
};

#endif
