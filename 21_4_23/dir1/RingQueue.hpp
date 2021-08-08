#pragma once 

#include <iostream>
#include <vector>
#include <unistd.h>
#include <semaphore.h>

#define NUM 10

class RingQueue
{
  private:
    std::vector<int> v;
    int max_cap;
    sem_t sem_blank; //生产者 表示空格子
    sem_t sem_data; //消费者 表示数据

    int c_index; //索引下标 消费者
    int p_index; //生产者

  private:
    void P(sem_t &s)
    {
      sem_wait(&s);
    }

    void V(sem_t &s)
    {
      sem_post(&s);
    }

  public:
    RingQueue(int _cap = NUM)
      :max_cap(_cap)
       ,v(10)
    {
      sem_init(&sem_blank, 0, max_cap); //初始化生产者信号量，初始值为队列容量最大值
      sem_init(&sem_data, 0, 0); //初始化消费者信号量，初始值为0

       c_index = 0;
       p_index = 0;
    }

    void Get(int &out) //消费者，获取队列数据
    {
        P(sem_data);
        
        //消费
        out = v[c_index];
        c_index++;
        c_index %= max_cap; //防止数组下标越界
        V(sem_blank);
        
    }

    void Put(const int &in) //生产者，往队列里写入数据
    {
      P(sem_blank);

      //生产
      v[p_index] = in;
      p_index++;
      p_index %= max_cap;
      V(sem_data);
    }

    ~RingQueue()
    {
      sem_destroy(&sem_blank);
      sem_destroy(&sem_data);

      c_index = 0;
      p_index = 0;
    }
};

