#include <stdio.h>
#include <stdlib.h>

int g_val = 10;
int g_unval;

int main(int argc, char* argv[], char* env[])
{
  printf("code addr: %p\n", main);
  printf("g addr: %p\n", &g_val);
  printf("g uninit addr: %p\n", &g_unval);
  
  char* mem = (char*)malloc(10);
  printf("heap addr: %p\n", mem);

  printf("stack addr: %p\n", &mem);

  printf("opt addr: %p\n", argv[0]);
  printf("opt addr: %p\n", argv[argc - 1]);

  printf("env addr: %p\n", env[0]);

  return 0;
}
