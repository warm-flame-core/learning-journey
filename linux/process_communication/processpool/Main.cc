#include "ProcessPool.hpp"

int main()
{
    ProcessPool pp(5);
    pp.Start();
    int task_code = 0;
    int cnt = 10;
    while (cnt--)
    {
        pp.Run();
        sleep(1);
    }
    pp.Stop();
    return 0;
}
