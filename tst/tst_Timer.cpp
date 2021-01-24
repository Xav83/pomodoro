#include "MockTimer.hpp"
#include "Timer.hpp"
#include "gtest/gtest.h"
#include <chrono>

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

// NOLINTNEXTLINE
TEST(tst_Timer, Equality) {
  pomodoro::Timer timer("name", std::chrono::milliseconds(42));
  pomodoro::Timer timerNotEqual_1("other name", std::chrono::milliseconds(42));
  pomodoro::Timer timerNotEqual_2("name", std::chrono::milliseconds(69));
  pomodoro::Timer timerEqual("name", std::chrono::milliseconds(42));

  EXPECT_EQ(timer, timerEqual);
  EXPECT_NE(timer, timerNotEqual_1);
  EXPECT_NE(timer, timerNotEqual_2);
}

namespace pomodoro {
// NOLINTNEXTLINE
TEST(tst_Timer, CallSleepForOnStart) {
  MockTimer timer("name", std::chrono::milliseconds(42));
  EXPECT_CALL(timer, sleep_for).Times(1);
  EXPECT_CALL(timer, run).Times(1);
  timer.start();
  ASSERT_TRUE(timer.timer_process.joinable());
  timer.timer_process.join();
}

// NOLINTNEXTLINE
TEST(tst_Timer, DefaultCallbackRunned) {
  MockTimer timer("name", std::chrono::milliseconds(42));
  auto hasBeenCalled = false;
  timer.callback = [&hasBeenCalled]() { hasBeenCalled = true; };
  timer.start();
  ASSERT_TRUE(timer.timer_process.joinable());
  timer.timer_process.join();
  EXPECT_TRUE(hasBeenCalled);
}

// NOLINTNEXTLINE
TEST(tst_Timer, SpecifiedCallbackRunned) {
  auto hasBeenCalled = false;
  MockTimer timer("name", std::chrono::milliseconds(42),
                  [&hasBeenCalled]() { hasBeenCalled = true; });
  timer.start();
  ASSERT_TRUE(timer.timer_process.joinable());
  timer.timer_process.join();
  EXPECT_TRUE(hasBeenCalled);
}

// NOLINTNEXTLINE
TEST(tst_Timer, TimerIsRunning) {
  MockTimer timer("name", std::chrono::milliseconds(42));

  ON_CALL(timer, sleep_for)
      .WillByDefault(::testing::Invoke([&timer](std::chrono::milliseconds) {
        EXPECT_TRUE(timer.isRunning());
      }));
  ON_CALL(timer, run).WillByDefault(::testing::Invoke([&timer]() {
    EXPECT_TRUE(timer.isRunning());
  }));

  EXPECT_CALL(timer, sleep_for).Times(1);
  EXPECT_CALL(timer, run).Times(1);
  timer.start();
  ASSERT_TRUE(timer.timer_process.joinable());
  timer.timer_process.join();
  EXPECT_FALSE(timer.isRunning());
}

// NOLINTNEXTLINE
TEST(tst_Timer, TimerRemaining) {
  MockTimer timer("name", std::chrono::seconds(42));

  auto initialTime = std::chrono::high_resolution_clock::now();
  auto timeAtFirstCheck = initialTime + std::chrono::seconds(2);
  auto timeAtTheEnd = initialTime + std::chrono::seconds(42);

  EXPECT_CALL(timer, sleep_for).Times(1);
  EXPECT_CALL(timer, run).Times(1);
  EXPECT_CALL(timer, get_current_time)
      .Times(2)
      .WillOnce(::testing::Return(initialTime))
      .WillOnce(::testing::Return(timeAtFirstCheck))
      .WillOnce(::testing::Return(timeAtTheEnd));

  timer.start();
  ASSERT_TRUE(timer.timer_process.joinable());
  EXPECT_EQ(timer.getRemainingTime(),
            std::chrono::duration_cast<std::chrono::seconds>(timeAtTheEnd -
                                                             timeAtFirstCheck));
  timer.timer_process.join();
  EXPECT_FALSE(timer.isRunning());
}
} // namespace pomodoro
