#include <stdio.h>
#include <unistd.h>

int main()
{
  printf("begin.............................\n");
 //  execl("/usr/bin/ls", "ls","-a", "-l", NULL);

 // execlp("ls", "ls", "-a", "-l", NULL);
 //char* arg[] = {
 //  "ls",
 //  "-a",
 //  "-l",
 //  NULL
 //};
 //  execvp("ls", arg);
 //  execv("/usr/bin/ls", arg);
  char* env[] = {
    "myenv=you_can_see_me!",
    NULL 
  };
  execle("./mycmd",  "./mycmd", NULL, env);
  printf("you should running here\n");
  return 0;
}
