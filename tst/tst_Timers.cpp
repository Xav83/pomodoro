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

// NOLINTNEXTLINE
TEST(tst_Timers, WithOneTimer) {
  pomodoro::Timers timers;
  timers.emplaceTimer("timer 1", std::chrono::milliseconds(1), []() {});

  EXPECT_NE(timers.cbegin(), timers.cend());
  EXPECT_EQ(std::distance(timers.cbegin(), timers.cend()), 1);
  EXPECT_EQ(timers.getTimer(0),
            pomodoro::Timer("timer 1", std::chrono::milliseconds(1), []() {}));
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  EXPECT_DEBUG_DEATH(timers.getTimer(1), "");
}

// NOLINTNEXTLINE
TEST(tst_Timers, WithSeveralTimers) {
  pomodoro::Timers timers;
  timers.emplaceTimer("timer 1", std::chrono::milliseconds(1), []() {});
  timers.emplaceTimer("timer 2", std::chrono::milliseconds(2), []() {});
  timers.emplaceTimer("timer 3", std::chrono::milliseconds(3), []() {});

  EXPECT_NE(timers.cbegin(), timers.cend());
  EXPECT_EQ(std::distance(timers.cbegin(), timers.cend()), 3);
  EXPECT_EQ(timers.getTimer(0),
            pomodoro::Timer("timer 1", std::chrono::milliseconds(1), []() {}));
  EXPECT_EQ(timers.getTimer(1),
            pomodoro::Timer("timer 2", std::chrono::milliseconds(2), []() {}));
  EXPECT_EQ(timers.getTimer(2),
            pomodoro::Timer("timer 3", std::chrono::milliseconds(3), []() {}));
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  EXPECT_DEBUG_DEATH(timers.getTimer(3), "");
}
