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
    void Send(int code)
    {
        int n = write(_wfd, &code, sizeof(code));
        (void)n;
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
        : _next(0)
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
    Channel& Select()
    {
        auto& c = _channels[_next];
        _next++;
        _next %= _channels.size();
        return c;
    }

private:
    std::vector<Channel> _channels;
    int _next;
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
    void PushTask(int taskcode)
    {
        // 选择信道
        auto& c = _cm.Select();
        std::cout << "选择了一个子进程：" << c.Name() << std::endl;
        c.Send(taskcode);
        std::cout << "任务码是：" << taskcode << std::endl;
    }
    void Work(int rfd)
    {
        while (1)
        {
            // 如果父进程写得慢，子进程读得快，那么子进程就会阻塞等待
            int code = 0;
            ssize_t n = read(rfd, &code, sizeof(code));
            if (n > 0)
            {
                if (n != sizeof(code))
                {
                    continue;
                }
                std::cout << "子进程[" << getpid() << "]收到任务码：" << code << std::endl;
            }
            else if (n == 0)
            {
                std::cout << "子进程退出" << std::endl;
            }
            else
            {
                std::cout << "读取失败" << std::endl;
            }
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
