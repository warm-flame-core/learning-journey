#include <stdio.h>
#define MAX 1024
typedef struct MYFIFE_IO
{
    int fileno;
    int flag;
    char outbuffer[MAX];
    int bufferlen;
}MY_FIFE;

MY_FIFE* Myfopen(const char* pathname, const char * mode);
void Myfclose(MY_FIFE *stream);
int Mywrite(MY_FIFE* stream, void* str, int size);
int Myfflash(MY_FIFE* stream);




