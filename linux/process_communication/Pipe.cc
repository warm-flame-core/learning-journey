#include <cstring>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

void ChildWrite(int wfd)
{
    char buffer[1024];
    int cnt = 0;
    while (true)
    {
        snprintf(buffer, sizeof(buffer), "我是子进程，我的pid：%d，cnt：%d",
                 getpid(), cnt++);
        write(wfd, buffer, strlen(buffer));
        sleep(1);
    }
}

void FatherRead(int rfd)
{
    char buffer[1024];
    while (true)
    {
        buffer[0] = 0;
        ssize_t n = read(rfd, buffer, sizeof(buffer) - 1);
        if (n > 0)
        {
            buffer[n] = 0;
            std::cout << "子进程的消息是" << buffer << std::endl;
        }
    }
}

int main()
{

    // 创建管道文件，测试发现管道文件占用文件描述符，是一种特殊的内存级别文件
    int fds[2] = {0};
    int n = pipe(fds);
    if (n < 0)
    {
        std::cerr << "pipe error" << std::endl;
        return 1;
    }
    std::cout << "fds[0]:" << fds[0] << std::endl; // 读端
    std::cout << "fds[1]:" << fds[1] << std::endl; // 写端

    // 创建子进程
    pid_t id = fork();
    if (id == 0)
    {
        close(fds[0]);
        // 子进程关闭读端
        ChildWrite(fds[1]);
        exit(0);
    }

    // 关闭读写通道
    // 父进程读，子进程写
    close(fds[1]);
    FatherRead(fds[0]);
    waitpid(id, nullptr, 0);

    return 0;
}