#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>




int main()
{
    umask(0);
    //int fp = open("log.txt", O_WRONLY|O_TRUNC|O_CREAT, 0666);
    int fp = open("log.txt", O_RDONLY);
    if(fp < 0)
    {
        perror("open error");
        return 1;
    }
    
    const char*msg = "hello world\n";
    char buf[1024];
    while(1)
    {
        ssize_t s = read(fp, buf, strlen(msg));//类⽐write 
        if(s > 0)
        {
            printf("%s", buf);
        }
        else
        {
            break;
        }
    }








    
    //const char*msg = "hello world\n";
    //int cout = 5;
    //while(cout--)
    //{
    //    // 系统调用程写入时不要带斜杠0，不然文件会乱码
    //    //write(fp, msg, strlen(msg)+1);
    //    write(fp, msg, strlen(msg));
    //}
    close(fp);
    return 0;
}









//int main()
//{
//    //FILE* fp = fopen("log.txt", "w");
//    FILE* fp = fopen("log.txt", "r");
//    if(!fp)
//    {
//        printf("fopen error\n");
//        return 1;
//    }
//    
//    char buf[1024];
//    const char *msg = "hello bit!\n";
//    while(1)
//    {
//        //注意返回值和参数，此处有坑，仔细查看man⼿册关于该函数的说明
//        ssize_t s = fread(buf, 1, strlen(msg), fp);
//        if(s > 0)
//        {
//            buf[s] = 0;
//            printf("%s", buf);
//        }
//        if(feof(fp))
//        {
//            break;
//        }
//    }
//
//
//
//
//
//    //const char *msg = "hello world\n";
//    //int cout = 5;
//    //while(cout--)
//    //{
//    //    fwrite(msg,strlen(msg),1,fp);
//    //}
//    fclose(fp);
//    return 0;
//}
