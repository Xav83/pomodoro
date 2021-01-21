#include "Timer.hpp"
#include "gtest/gtest.h"

// NOLINTNEXTLINE
TEST(tst_Timer, DefaultTimerNotRunning) {
  pomodoro::Timer timer("name", std::chrono::milliseconds(42));
  EXPECT_FALSE(timer.isRunning());
}
