#pragma once 

#include <iostream>
#include <queue>
#include <math.h>
#include <unistd.h>

#define NUM 5

class Task
{
  public:
    int base;

  public:
    Task()
    {}

    Task(int _b)
      :base(_b)
    {}

    void Run()
    {
      std::cout << "thread is[" << pthread_self() << "] task run ... done: base# " << base << " pow is# " << pow(base, 2) << std::endl;
    }

    ~Task()
    {}
};

class ThreadPool
{
  private:
    std::queue<Task*> q; //塞任务指针，而非任务，因为任务本身可能较大
    int max_num;
    pthread_mutex_t lock;
    pthread_cond_t cond; //只能消费者在该条件变量下等
  
  private:
    void LockQueue()
    {
      pthread_mutex_lock(&lock);
    }

    void UnlockQueue()
    {
      pthread_mutex_unlock(&lock);
    }

    bool IsEmpty()
    {
      return q.size() == 0;
    }

    void ThreadWait()
    {
      pthread_cond_wait(&cond, &lock);
    }

    void ThreadWakeup()
    {
      pthread_cond_signal(&cond);
    }

    static void* Routine(void* arg) //pthread_create函数第三个参数的回调函数只有一个参数，类的成员函数必有一个this，为了保证只有一个，用static修饰该函数
     {
       ThreadPool* this_p = (ThreadPool*)arg;
       while(true) // 线程池的线程永远不退出
       {
         this_p->LockQueue();
         while(this_p->IsEmpty())
         {
           this_p->ThreadWait();
         }

         Task t;
         this_p->Get(t);
         this_p->UnlockQueue();

         t.Run(); //任务取出来之后，属于线程的私有资源，所以执行的过程不用加锁，节省时间
       }
     }

  public:
     ThreadPool(int _max = NUM)
      :max_num(_max)
    {}

    void ThreadPoolInit() //把有风险的构造封装一个函数
    {
      pthread_mutex_init(&lock, nullptr);
      pthread_cond_init(&cond, nullptr);

      pthread_t t;
      for(int i = 0; i < max_num; i++)
      {
        pthread_create(&t, nullptr, Routine, this); //static对象不能访问非static方法，传this指针用于访问
      }
    }

    //server
    void Put(Task &in)
    {
      LockQueue();

      q.push(&in);

      UnlockQueue();

      ThreadWakeup();

      
    }

    //Thread pool t
    void Get(Task &out)
    {
      Task* t = q.front();
      q.pop();
      out = *t;
    }

    ~ThreadPool()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&cond);
    }

};
