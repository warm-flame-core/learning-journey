#pragma once

#include <sys/ipc.h>
#include <sys/shm.h>

#include <iostream>
#include <string>

const int gdefultid = 1;
const int gsize = 4096;
const std::string pathname = ".";
const int projid = 0x66;
#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)

class Shm
{
public:
    Shm()
        : _shmid(gdefultid), _size(gsize)
    {
    }
    void Crate()
    {
        key_t k = ftok(pathname.c_str(), projid);
        if (k < 0)
        {
            ERR_EXIT("ftok\n");
        }
        printf("key:0x%x\n", k);
        _shmid = shmget(k, _size, IPC_CREAT | IPC_EXCL);
        if (_shmid < 0)
        {
            ERR_EXIT("shmget\n");
        }
        printf("shmid:%d\n", _shmid);
    }
    ~Shm()
    {
    }

private:
    int _shmid;
    int _size;
};
