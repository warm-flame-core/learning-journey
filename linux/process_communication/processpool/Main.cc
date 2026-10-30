#include "ProcessPool.hpp"

int main()
{
    ProcessPool pp(5);
    pp.Start();
    pp.Debug();
    sleep(1000);
    return 0;
}
