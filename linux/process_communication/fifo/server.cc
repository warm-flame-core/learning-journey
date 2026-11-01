

#include "comm.hpp"

int main()
{
    // 新建管道
    umask(0);
    NameFifo fifo(PATH, FIFO_FIFE);
    FileOper readerfile(PATH, FIFO_FIFE);
    // 打开文件
    readerfile.OpenForRead();
    // 阅读管道文件
    readerfile.Read();
    // 删除管道文件
    readerfile.Close();
    return 0;
}
