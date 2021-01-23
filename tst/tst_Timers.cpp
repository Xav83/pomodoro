#include "Timers.hpp"
#include "gtest/gtest.h"

// NOLINTNEXTLINE
TEST(tst_Timers, DefaultTimersHasNoTimerRunning) {
  pomodoro::Timers timers;
  EXPECT_FALSE(timers.hasOneTimerRunning());
}

// NOLINTNEXTLINE
TEST(tst_Timers, DefaultTimersHasNoTimer) {
  pomodoro::Timers timers;
  EXPECT_EQ(timers.cbegin(), timers.cend());
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  EXPECT_DEBUG_DEATH(timers.getTimer(0), "");
}
