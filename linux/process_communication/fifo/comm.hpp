#pragma once

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)

#define PATH "."
#define FIFO_FIFE "fifo"

class NameFifo
{
public:
    NameFifo(const std::string& path, const std::string& name)
        : _path(path), _name(name)
    {
        _fifoname = _path + "/" + _name;
        int n = mkfifo(_fifoname.c_str(), 0666);
        if (n < 0)
        {
            ERR_EXIT("mkfifo");
        }
        else
        {
            std::cout << "mkfifo success" << std::endl;
        }
    }
    ~NameFifo()
    {
        int n = unlink(_fifoname.c_str());
        if (n == 0)
        {
            std::cout << "remove success" << std::endl;
        }
        else
        {
            ERR_EXIT("remove");
        }
    }

private:
    std::string _path;
    std::string _name;
    std::string _fifoname;
};

class FileOper
{
public:
    FileOper(const std::string& path, const std::string& name)
        : _path(path), _name(name), _fd(-1)
    {
        _fifoname = _path + "/" + _name;
    }
    void OpenForRead()
    {
        _fd = open(FIFO_FIFE, O_RDONLY);
        if (_fd < 0)
        {
            ERR_EXIT("OpenForRead");
        }
        std::cout << "mkfifo  open success" << std::endl;
    }
    void OpenForWrite()
    {
        _fd = open(FIFO_FIFE, O_WRONLY);
        if (_fd < 0)
        {
            ERR_EXIT("OpenForWrite");
        }
        std::cout << "mkfifo  open success" << std::endl;
    }
    void Read()
    {
        while (1)
        {
            char buffer[1024] = {0};
            int nummber = read(_fd, buffer, sizeof(buffer) - 1);
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
                ERR_EXIT("read");
            }
        }
    }
    void Write()
    {
        std::string message;
        int cnt = 1;
        pid_t id = getpid();
        while (1)
        {
            std::cout << "Plase Enter #";
            std::getline(std::cin, message);
            message += ",message number:" + std::to_string(cnt++) + "[" + std::to_string(id) + "]";
            write(_fd, message.c_str(), message.size());
        }
    }
    void Close()
    {
        if (_fd > 0)
            close(_fd);
    }
    ~FileOper()
    {
    }

private:
    std::string _path;
    std::string _name;
    std::string _fifoname;
    int _fd;
};
