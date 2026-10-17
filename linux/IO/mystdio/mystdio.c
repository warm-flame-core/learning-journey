#include "mystdio.h"
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
MY_FIFE* BuyFile(int fd, int flag)
{
    MY_FIFE* f = (MY_FIFE*)malloc(sizeof(MY_FIFE));
    if(f == NULL) return NULL;
    f->flag = flag;
    f->bufferlen = 0;
    f->fileno = fd;
    f->flash_method = LINE_FLASH;
    memset(f->outbuffer, 0, sizeof(f->outbuffer));
    return f;
}
MY_FIFE* Myfopen(const char* pathname, const char * mode)
{
    int fd = -1;
    int flag = 0;
    if(strcmp(mode, "w") == 0)
    {
        flag = O_CREAT | O_WRONLY | O_TRUNC;
        fd = open(pathname, flag, 0666);
    }
    else if(strcmp(mode, "a") == 0)
    {
        flag = O_CREAT | O_WRONLY | O_APPEND;
        fd = open(pathname, flag, 0666);
    }
    else if(strcmp(mode, "r") == 0)
    {
        flag = O_RDWR;
        fd = open(pathname, flag);
    }
    else
    {

    }
    return BuyFile(fd, flag);
}
void Myfclose(MY_FIFE *stream)
{
    if(stream->fileno <= 0) return;
    Myfflash(stream);
    close()
}
int Mywrite(MY_FIFE* stream, void* str, int size)
{
    memcpy(stream->outbuffer + stream->bufferlen, str, size);
    stream->bufferlen += size;
    // 尝试判断
    if((stream->flash_method & LINE_FLASH) && stream->outbuffer[stream->bufferlen - 1] == '\n')
    {
        Myfflash(stream);
    }
    return 0;
}
void Myfflash(MY_FIFE* stream)
{
    int n = write(stream->fileno, stream->outbuffer, stream->bufferlen);
    (void) n;
    fsync(stream->fileno);
    stream->bufferlen = 0;
}
