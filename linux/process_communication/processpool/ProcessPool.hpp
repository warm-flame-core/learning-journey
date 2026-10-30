#ifndef __PROCESSPOOL_HPP__
#define __PROCESSPOOL_HPP__

#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

// 先描述
class Channel
{
public:
    Channel(int wfd, pid_t subid)
        : _wfd(wfd), _subid(subid)
    {
        _name = "Channel-" + std::to_string(wfd) + "-" + std::to_string(subid);
    }
    ~Channel()
    {
    }
    int Fd() { return _wfd; }
    pid_t Subid() { return _subid; }
    std::string Name() { return _name; }

private:
    int _wfd;
    pid_t _subid;
    std::string _name;
};

// 再组织
class ChannelManager
{
public:
    ChannelManager()
    {
    }
    ~ChannelManager()
    {
    }
    void PrintChannel()
    {
        for (auto& channel : _channels)
        {
            std::cout << channel.Name() << std::endl;
        }
    }
    void Insert(int wfd, pid_t subid)
    {
        _channels.emplace_back(wfd, subid);
    }

private:
    std::vector<Channel> _channels;
};
class ProcessPool
{
public:
    ProcessPool(int num)
        : _process_num(num)
    {
    }
    ~ProcessPool()
    {
    }
    void Work(int rfd)
    {
        while (1)
        {
            std::cout << "我是子进程：" << rfd << std::endl;
            sleep(5);
        }
    }
    void Debug()
    {
        _cm.PrintChannel();
    }
    bool Start()
    {
        for (int i = 0; i < _process_num; i++)
        {
            // 创建管道
            int pipefd[2] = {0};
            int n = pipe(pipefd);
            if (n < 0)
            {
                return false;
            }

            // 创建子进程
            pid_t subid = fork();
            if (subid < 0)
            {
                return false;
            }
            else if (subid == 0)
            {
                // 子进程要做的事情
                // 子进程关闭写端
                close(pipefd[1]);
                Work(pipefd[0]);
                close(pipefd[0]);
                exit(0);
            }
            else
            {
                // 父进程要做的事情
                close(pipefd[0]);
                // 把写段和子进程pid保存起来
                _cm.Insert(pipefd[1], subid);
            }
        }
        return true;
    }

private:
    ChannelManager _cm;
    int _process_num;
};

#endif
