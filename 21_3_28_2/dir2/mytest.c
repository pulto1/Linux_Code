#include <stdio.h>
#include "myadd.h"
#include "mysub.h"

int main()
{
  int x = 10;
  int y = 20;
  printf("add is %d\n", MyAdd(x, y)); 
  printf("sub is %d\n", MySub(x, y));
  printf("hello world\n");
  return 0;
}
