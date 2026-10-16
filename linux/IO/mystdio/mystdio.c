#include "mystdio.h"

MY_FIFE* Myfopen(const char* pathname, const char * mode);
void Myfclose(MY_FIFE *stream);
int Mywrite(MY_FIFE* stream, void* str, int size);
int Myfflash(MY_FIFE* stream);
