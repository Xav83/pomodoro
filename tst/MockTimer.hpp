#pragma once

#include "Timer.hpp"
#include "gmock/gmock.h"

namespace pomodoro {
class MockTimer : public Timer {
public:
  MockTimer(
      std::string_view name, std::chrono::milliseconds delayInMs,
      std::function<void()> callback = []() {})
      : pomodoro::Timer(name, delayInMs, std::move(callback)) {}
  MOCK_METHOD(void, sleep_for, (std::chrono::milliseconds), (override));
  MOCK_METHOD(void, run, (), (override));
  MOCK_METHOD(std::chrono::time_point<std::chrono::high_resolution_clock>,
              get_current_time, (), (const));
};
} // namespace pomodoro