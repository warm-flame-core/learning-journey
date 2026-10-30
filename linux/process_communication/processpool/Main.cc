#include "ProcessPool.hpp"

int main()
{
    ProcessPool pp(5);
    pp.Start();
    // pp.Debug();
    int task_code = 0;
    while (1)
    {
        pp.Run();
        sleep(1);
    }
    sleep(1000);
    return 0;
}
