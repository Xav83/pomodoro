#pragma once

namespace pomodoro
{
class Timer
{
public:
    Timer(int delayInMs);
    ~Timer();

    void start();

private:
    int delayInMs{0};
};
}
