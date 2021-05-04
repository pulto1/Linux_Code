#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[], char* env[])
{
  for(int i = 0; i < argc; i++)
  {
    cout << "argv[" << i << "]" << " : " << argv[i] << endl;
  }
  return 0;
}
