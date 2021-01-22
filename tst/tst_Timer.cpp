#include "Timer.hpp"
#include "gmock/gmock.h"
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

namespace pomodoro {
class MockTimer : public Timer {
public:
  MockTimer(
      std::string_view name, std::chrono::milliseconds delayInMs,
      std::function<void()> callback = []() {})
      : pomodoro::Timer(name, delayInMs, callback) {}
  MOCK_METHOD(void, sleep_for, (std::chrono::milliseconds), (override));
  MOCK_METHOD(void, run, (), (override));
};

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
} // namespace pomodoro
