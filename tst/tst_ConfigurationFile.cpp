#include "ConfigurationFile.hpp"
#include "gtest/gtest.h"

// NOLINTNEXTLINE
TEST(tst_ConfigurationFile, EmptyPathAsConfigurationFile) {
  std::filesystem::path path;
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  EXPECT_DEBUG_DEATH(pomodoro::ConfigurationFile conf_file(path), "");
}
