#include "Timer.hpp"
#include <cassert>
#include <chrono>
#include <thread>

using pomodoro::Timer;

Timer::Timer(std::string_view name_, std::chrono::milliseconds delayInMs_,
             std::function<void()> callback_)
    : name(name_), delayInMs(delayInMs_), callback(std::move(callback_)) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(not name.empty());
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(delayInMs != std::chrono::milliseconds(0));
}

Timer::~Timer() = default;

void Timer::start() {
  isCurrentlyRunning = true;
  timeAtStart = std::chrono::high_resolution_clock::now();
  std::thread t([this]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(delayInMs));
    isCurrentlyRunning = false;
    callback();
  });
  t.detach();
}

bool Timer::isRunning() const { return isCurrentlyRunning; }

std::chrono::seconds Timer::getRemainingTime() const {
  if (isRunning()) {
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
        delayInMs - (std::chrono::high_resolution_clock::now() - timeAtStart));
    return elapsed;
  }
  return std::chrono::duration_cast<std::chrono::seconds>(delayInMs);
}

std::string_view Timer::getName() const { return name; }
