#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int ticket = 100;
pthread_mutex_t lock;

void* get_ticket(void* arg)
{
  int num = (long long)arg;
  
  while(1)
  {
    pthread_mutex_lock(&lock);
    if(ticket > 0)
    {
      usleep(1000);
      printf("thread %d, get a ticket, No: %d\n", num, ticket);
      ticket--;
      pthread_mutex_unlock(&lock);
    }

    else 
    {
      pthread_mutex_unlock(&lock);
      break;
    }
  }

  return (void*)0;
}

int main()
{
  pthread_t tid[4];
  
  long long i = 0;
  pthread_mutex_init(&lock, NULL);
  for(; i < 4; i++)
  {
    pthread_create(tid + i, NULL, get_ticket, (void*)i);
  }

  for(i = 0; i < 4; i++)
  {
    pthread_join(tid[i], NULL);
  }

  pthread_mutex_destroy(&lock);
  
  return 0;
}
