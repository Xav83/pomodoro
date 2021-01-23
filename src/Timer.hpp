#pragma once

#include "gtest/gtest_prod.h"
#include <chrono>
#include <functional>
#include <mutex>
#include <string_view>
#include <thread>

namespace pomodoro {
class Timer {
public:
  Timer(
      std::string_view name_, std::chrono::milliseconds delayInMs_,
      std::function<void()> callback_ = []() {});
  Timer(const Timer &other);
  virtual ~Timer();

  void start();

  bool isRunning() const;

  std::chrono::seconds getRemainingTime() const;
  std::string_view getName() const;

private:
  virtual void sleep_for(std::chrono::milliseconds delay);
  virtual void run();
  virtual std::chrono::time_point<std::chrono::high_resolution_clock>
  get_current_time() const;

  FRIEND_TEST(tst_Timer, CallSleepForOnStart);
  FRIEND_TEST(tst_Timer, DefaultCallbackRunned);
  FRIEND_TEST(tst_Timer, SpecifiedCallbackRunned);
  FRIEND_TEST(tst_Timer, TimerIsRunning);
  FRIEND_TEST(tst_Timer, TimerRemaining);

  std::string_view name;
  std::chrono::milliseconds delayInMs{0};
  std::function<void()> callback;
  std::mutex lockIsRunning;
  bool isCurrentlyRunning{false};
  std::chrono::time_point<std::chrono::high_resolution_clock> timeAtStart;
  std::thread timer_process;
};
} // namespace pomodoro
