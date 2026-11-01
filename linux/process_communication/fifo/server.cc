#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "comm.hpp"

int main()
{
    // 新建管道
    umask(0);
    int n = mkfifo(FIFO_FIFE, 0666);
    if (n < 0)
    {
        std::cerr << "mkfifo error" << std::endl;
        return 1;
    }
    std::cout << "mkfifo success" << std::endl;
    // 打开文件
    int fd = open(FIFO_FIFE, O_RDONLY);
    if (fd < 0)
    {
        std::cerr << "open error" << std::endl;
        return 2;
    }
    std::cout << "mkfifo  open success" << std::endl;
    // 阅读管道文件
    while (1)
    {
        char buffer[1024] = {0};
        int nummber = read(fd, buffer, sizeof(buffer) - 1);
        if (nummber > 0)
        {
            buffer[nummber] = 0;
            std::cout << "say:" << buffer << std::endl;
        }
        else if (nummber == 0)
        {
            std::cout << "cilent close" << std::endl;
            break;
        }
        else
        {
            std::cerr << "error" << std::endl;
            return 3;
        }
    }

    close(fd);
    // 删除管道文件
    unlink(FIFO_FIFE);
    return 0;
}
