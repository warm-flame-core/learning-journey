#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{   
    
    printf("父进程开始，pif:%d",getpid());
    pid_t id = fork();
    if(id < 0)
    {
        perror("fork");
        return 1;
    }
    else if(id == 0)
    {
        while(1)
        {
            sleep(1);
            printf("这是一个子进程！，我的pid：%d,我的父进程id：%d\n",getpid(),getppid());
        }
    }
    else 
    {
        while(1)
        {
            sleep(1);
            printf("这是一个父进程！，我的pid：%d,我的父进程id：%d\n",getpid(),getppid());
        }
    }
    printf("进程开始，pid:%d",getpid());




    
   // printf("父进程开始，pif:%d",getpid());
   // fork();
   // printf("子进程开始，pid:%d",getpid());



   // while(1)
   // {
   //     chdir("/home/xjw"); //更改进程的工作路径，可以影响创建文件
   //     fopen("test.txt","a");
   //     sleep(1);
   //     printf("这是一个进程！，我的pid：%d,我的父进程id：%d\n",getpid(),getppid());

   // }
   return 0;
}
