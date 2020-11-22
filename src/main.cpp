#include "Timer.hpp"
#include <iostream>

int main()
{
    pomodoro::Timer t;
    std::cout << "Hello..." ;
    t.setTimeoutIn(10000);
    std::cout << "World !" << std::endl;
    return 0;
}
