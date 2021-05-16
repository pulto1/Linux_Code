#include <stdio.h>
#include <stdlib.h>

int main()
{
  int sum = 0;
  for(int i = 0; i <= 100; i++)
  {
    sum += i;
  }

  printf("sum[1~100] is %d\n", sum);
  printf("myenv: %s\n", getenv("myenv"));
  return 0;
}
