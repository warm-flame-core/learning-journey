#pragma once

#include <ctime>
#include <iostream>
#include <vector>

typedef void (*task_t)();

void Printlog()
{
    std::cout << "一个打印日志的任务" << std::endl;
}
void Downdload()
{
    std::cout << "一个下载的任务" << std::endl;
}
void Upload()
{
    std::cout << "一个上传的任务" << std::endl;
}

class TaskManager
{
public:
    TaskManager()
    {
        srand(time(nullptr));
    }
    ~TaskManager()
    {
    }
    void Register(task_t task)
    {
        _tasks.push_back(task);
    }
    int Code()
    {
        return rand() % _tasks.size();
    }
    void Execute(int code)
    {
        if (code >= 0 && code < _tasks.size())
        {
            // 方括号只是取出来，要加括号才是执行，不然不会执行
            _tasks[code]();
        }
    }

private:
    std::vector<task_t> _tasks;
};
