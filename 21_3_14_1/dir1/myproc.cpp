#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std;

int main()
{
  pid_t id = fork();

  if(id == 0)
  {
    //child
    int count = 0;
    while(1)
    {
      sleep(1);
      cout << "child ...  " << count << endl;
      if(count == 5)
      {
        break;
      }

      count++;
    }

    exit(0);
  }

  else 
  {
    cout << "father before..." << endl;
    wait(NULL);
    cout << "father after..." << endl;
    //father
    //int count = 0;
    //while(1)
    //{
    //  sleep(1);
    //  cout << "father ..." << count << endl;
    //  if(count == 15)
    //  {
    //    wait(NULL);
    //  }

    //  if(count == 17)
    //  {
    //    break;
    //  }

    //  count++;
    //}
  }

  cout << "hello" << endl;
  return 0;
}

//int exe()
//{
//  return 123;
////  exit(123);
//}
//
//int main()
//{
//  exe();
//  cout << "you should running here!" << endl;
//  
//  return 0;
//  cout << "hello";
//  sleep(3);
//
//  _exit(123);
//
//  return 0;
//  int x = 1 / 0;

//  pid_t id = fork();
//  sleep(3);
//  cout << "hello" << endl;

//  cout << "I am a process: " << getpid() << endl;
//
//  pid_t id = fork();
//
//  if(id < 0)
//  {
//    //error
//    cerr << "fork error" << endl;
//    return 1;
//  }
//
//  else if(id == 0)
//  {
//    //child
//    cout << "I am son: " << getpid() << endl;
//    sleep(3);
//  }
//
//  else
//  {
//    //father
//    cout << "I am father: " << getpid() << "   myson pid: " << id << endl;
//    sleep(3);
//  }
    
//  return 0;

