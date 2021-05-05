#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[], char* env[])
{
  cout << getenv("MYENV") << endl;
 // cout << getenv("PATH") << endl;
 // cout << getenv("PWD")  <<endl;
 // for(int i = 0; env[i]; i++)
 // {
 //   cout << i << ":" << env[i] << endl;
 // }
  return 0;
}
