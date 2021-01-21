#include "Timer.hpp"
#include "gtest/gtest.h"

// NOLINTNEXTLINE
TEST(tst_Timer, TimerWithoutName) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  EXPECT_DEBUG_DEATH(pomodoro::Timer timer("", std::chrono::milliseconds(42)),
                     "");
}

// NOLINTNEXTLINE
TEST(tst_Timer, TimerWithoutAnyDelay) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  EXPECT_DEBUG_DEATH(
      pomodoro::Timer timer("name", std::chrono::milliseconds(0)), "");
}

// NOLINTNEXTLINE
TEST(tst_Timer, DefaultTimer) {
  pomodoro::Timer timer("name", std::chrono::milliseconds(42));
  EXPECT_FALSE(timer.isRunning());
  EXPECT_EQ(timer.getName(), "name");
  EXPECT_EQ(timer.getRemainingTime(),
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::milliseconds(42)));
}
