#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "comm.hpp"

int main()
{
    // 打开管道文件
    int fd = open(FIFO_FIFE, O_WRONLY);
    if (fd < 0)
    {
        std::cerr << "open error" << std::endl;
        return 1;
    }
    std::cout << "mkfifo  open success" << std::endl;

    // 写入管道文件
    std::string message;
    int cnt = 1;
    pid_t id = getpid();
    while (1)
    {
        std::cout << "Plase Enter #";
        std::getline(std::cin, message);
        message += ",message number:" + std::to_string(cnt++) + "[" + std::to_string(id) + "]";
        write(fd, message.c_str(), message.size());
    }
    close(fd);
    return 0;
}
