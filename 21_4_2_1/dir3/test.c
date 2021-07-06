#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
  mkfifo("./fofo",0644);
  return 0;
}
