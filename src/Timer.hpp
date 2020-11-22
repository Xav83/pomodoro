#pragma once

namespace pomodoro
{
class Timer
{
public:
    Timer(int delayInMs);
    ~Timer();

    void start();

    bool isRunning() const;

private:
    int delayInMs{0};
    bool isCurrentlyRunning{false}, hasRun{false};
};
}
