#ifndef __PROCESSPOOL_HPP__
#define __PROCESSPOOL_HPP__

#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "Task.hpp"
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
    void Close()
    {
        close(_wfd);
    }
    void Wait()
    {
        pid_t rid = waitpid(_subid, nullptr, 0);
        (void)rid;
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

    // 关闭父进程wfd
    void CloseSubProcess()
    {
        for (auto& channel : _channels)
        {
            channel.Close();
            std::cout << "关闭的子进程是：" << channel.Name() << std::endl;
        }
    }
    // 回收所有子进程
    void WaitSubProcess()
    {
        for (auto& channel : _channels)
        {
            channel.Wait();
            std::cout << "回收的子进程是：" << channel.Name() << std::endl;
        }
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
        _tasks.Register(Printlog);
        _tasks.Register(Downdload);
        _tasks.Register(Upload);
    }
    ~ProcessPool()
    {
    }
    void Stop()
    {
        // 关闭父进程wfd
        _cm.CloseSubProcess();
        // 回收所有子进程
        _cm.WaitSubProcess();
    }

    void Run()
    {
        // 选择任务
        int taskcode = _tasks.Code();
        // 选择信道
        auto& c = _cm.Select();
        std::cout << "选择了一个子进程：" << c.Name() << std::endl;
        // 发送任务
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
                _tasks.Execute(code);
                std::cout << std::endl;
                std::cout << std::endl;
            }
            else if (n == 0)
            {
                std::cout << "子进程退出" << std::endl;
                break;
                // 要记得退出之后结束循环，不然一直是0会死循环
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
    TaskManager _tasks;
};

#endif
