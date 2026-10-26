#include <stdio.h>
#define MAX 1024
#define NONE_FLASH (1 << 0)
#define LINE_FLASH (1 << 1)
#define FULL_FLASH (1 << 2)
typedef struct MYFIFE_IO
{
    int fileno;
    int flag;
    char outbuffer[MAX];
    int bufferlen;
    int flash_method;
} MY_FIFE;

MY_FIFE* Myfopen(const char* pathname, const char* mode);
void Myfclose(MY_FIFE* stream);
int Mywrite(MY_FIFE* stream, void* str, int size);
void Myfflash(MY_FIFE* stream);
