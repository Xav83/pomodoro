#include "gtest/gtest.h"
#include "Configuration.hpp"
#include "color/Dictionary.hpp"

TEST(tst_Configuration, DefaultConfiguration) {
pomodoro::Configuration conf;

  EXPECT_EQ(conf.getColorId(), pomodoro::color::Id::default_1);
  EXPECT_EQ(conf.getWorkTime(), std::chrono::minutes(pomodoro::numbers::default_work_time));
  EXPECT_EQ(conf.getBreakTime(), std::chrono::minutes(pomodoro::numbers::default_break_time));
  EXPECT_EQ(conf.getColors(), pomodoro::color::dictionary[static_cast<size_t>(pomodoro::color::Id::default_1)]);
  EXPECT_EQ(conf.getLongBreakTime(), std::chrono::minutes(pomodoro::numbers::default_long_break_time));
}
