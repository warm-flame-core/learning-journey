#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
   printf("我的程序运行开始\n");
   if(fork() == 0)
   {
       char* const argv[] = {"ls", "-l", "-a", NULL};
        //execl("/usr/bin/ls","ls","-l","-a",NULL);
        //execlp("ls","ls","-l","-a",NULL);
        execv("/usr/bin/ls", argv);
        //execl("./other","other", NULL);
        exit(1);
   }
   waitpid(-1, NULL, 0);
   printf("我的程序运行完了\n");
    return 0;
}
