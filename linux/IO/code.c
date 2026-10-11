#include <stdio.h>
#include <string.h>

int main()
{
    //FILE* fp = fopen("log.txt", "w");
    FILE* fp = fopen("log.txt", "r");
    if(!fp)
    {
        printf("fopen error\n");
        return 1;
    }
    
    char buf[1024];
    const char *msg = "hello bit!\n";
    while(1)
    {
        //注意返回值和参数，此处有坑，仔细查看man⼿册关于该函数的说明
        ssize_t s = fread(buf, 1, strlen(msg), fp);
        if(s > 0)
        {
            buf[s] = 0;
            printf("%s", buf);
        }
        if(feof(fp))
        {
            break;
        }
    }





    //const char *msg = "hello world\n";
    //int cout = 5;
    //while(cout--)
    //{
    //    fwrite(msg,strlen(msg),1,fp);
    //}
    fclose(fp);
    return 0;
}
