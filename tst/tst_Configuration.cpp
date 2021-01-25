#include "Configuration.hpp"
#include "color/Dictionary.hpp"
#include "gtest/gtest.h"

// NOLINTNEXTLINE
TEST(tst_Configuration, DefaultConfiguration) {
  pomodoro::Configuration conf;

  EXPECT_EQ(conf.getColorId(), pomodoro::color::Id::default_1);
  EXPECT_EQ(conf.getWorkTime(),
            std::chrono::minutes(pomodoro::numbers::default_work_time));
  EXPECT_EQ(conf.getBreakTime(),
            std::chrono::minutes(pomodoro::numbers::default_break_time));
  EXPECT_EQ(conf.getColors(), pomodoro::color::dictionary[static_cast<size_t>(
                                  pomodoro::color::Id::default_1)]);
  EXPECT_EQ(conf.getLongBreakTime(),
            std::chrono::minutes(pomodoro::numbers::default_long_break_time));
}

// NOLINTNEXTLINE
TEST(tst_Configuration, CustomConfigurationConstuctor) {
  pomodoro::Configuration conf(
      pomodoro::color::Id::default_2, std::chrono::minutes(42),
      std::chrono::minutes(666), std::chrono::minutes(13));

  EXPECT_EQ(conf.getColorId(), pomodoro::color::Id::default_2);
  EXPECT_EQ(conf.getWorkTime(), std::chrono::minutes(42));
  EXPECT_EQ(conf.getBreakTime(), std::chrono::minutes(666));
  EXPECT_EQ(conf.getColors(), pomodoro::color::dictionary[static_cast<size_t>(
                                  pomodoro::color::Id::default_2)]);
  EXPECT_EQ(conf.getLongBreakTime(), std::chrono::minutes(13));
}

// NOLINTNEXTLINE
TEST(tst_Configuration, CustomConfigurationSetters) {
  pomodoro::Configuration conf;

  conf.setColorId(pomodoro::color::Id::default_2);
  conf.setWorkTime(std::chrono::minutes(42));
  conf.setBreakTime(std::chrono::minutes(666));
  conf.setLongBreakTime(std::chrono::minutes(13));

  EXPECT_EQ(conf.getColorId(), pomodoro::color::Id::default_2);
  EXPECT_EQ(conf.getWorkTime(), std::chrono::minutes(42));
  EXPECT_EQ(conf.getBreakTime(), std::chrono::minutes(666));
  EXPECT_EQ(conf.getColors(), pomodoro::color::dictionary[static_cast<size_t>(
                                  pomodoro::color::Id::default_2)]);
  EXPECT_EQ(conf.getLongBreakTime(), std::chrono::minutes(13));
}

// NOLINTNEXTLINE
TEST(tst_Configuration, GettingColorsWhenNoColorIsSpecified) {
  pomodoro::Configuration conf;

  conf.setColorId(pomodoro::color::Id::no_color);
  EXPECT_EQ(conf.getColorId(), pomodoro::color::Id::no_color);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  EXPECT_DEBUG_DEATH(conf.getColors(), "");
}
