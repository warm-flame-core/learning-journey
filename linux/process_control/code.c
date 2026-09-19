#include <stdio.h>
#include <string.h>
#include <errno.h>
int main()
{
   // int i = 0;
   // for(;i<134;i++)
   // {
   //     printf("%d:%s\n",i,strerror(i));

   // }







    printf("Hello World\n");
    FILE *fp = fopen("log.txt","r");
    // if(fp == NULL)  return 1;
    // 可以用系统规定的退出码
    if(fp == NULL)  return errno;
    fclose(fp);
    return 0;
}
