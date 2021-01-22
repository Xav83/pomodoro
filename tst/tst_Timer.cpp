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
  MockTimer(std::string_view name, std::chrono::milliseconds delayInMs)
      : pomodoro::Timer(name, delayInMs) {}
  MOCK_METHOD(void, sleep_for, (std::chrono::milliseconds), (override));
  MOCK_METHOD(void, run, (), (override));
};

// NOLINTNEXTLINE
TEST(tst_Timer, CallSleepForOnStart) {
  MockTimer timer("name", std::chrono::milliseconds(42));
  EXPECT_CALL(timer, sleep_for);
  EXPECT_CALL(timer, run);
  timer.start();
  ASSERT_TRUE(timer.timer_process.joinable());
  timer.timer_process.join();
}

// NOLINTNEXTLINE
TEST(tst_Timer, CallbackRunned) {
  MockTimer timer("name", std::chrono::milliseconds(42));
  auto hasBeenCalled = false;
  timer.callback = [&hasBeenCalled]() { hasBeenCalled = true; };
  timer.start();
  ASSERT_TRUE(timer.timer_process.joinable());
  timer.timer_process.join();
  EXPECT_TRUE(hasBeenCalled);
}
} // namespace pomodoro
