#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("我的程序运行开始\n");
    execl("/usr/bin/ls","ls","-l","-a",NULL);
    return 0;
}
