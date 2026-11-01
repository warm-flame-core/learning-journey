
#include "comm.hpp"

int main()
{
    FileOper writerfile(PATH, FIFO_FIFE);
    // 打开管道文件
    writerfile.OpenForWrite();

    // 写入管道文件
    writerfile.Write();
    // 关闭
    writerfile.Close();

    return 0;
}
