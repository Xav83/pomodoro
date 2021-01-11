#include "ConfigurationFile.hpp"
#include "utility/FilesDictionary.hpp"
#include "gtest/gtest.h"

// NOLINTNEXTLINE
TEST(tst_ConfigurationFile, EmptyPathAsConfigurationFile) {
  std::filesystem::path path;
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  EXPECT_DEBUG_DEATH(pomodoro::ConfigurationFile conf_file(path), "");
}

// NOLINTNEXTLINE
TEST(tst_ConfigurationFile, FolderAsConfigurationFile) {
  std::filesystem::path path = "./folder/";
  std::filesystem::create_directory(path);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  EXPECT_DEBUG_DEATH(pomodoro::ConfigurationFile conf_file(path), "");
  std::filesystem::remove(path);
}

// NOLINTNEXTLINE
TEST(tst_ConfigurationFile, PomodoroConfigurationFileAsConfigurationFile) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  pomodoro::ConfigurationFile conf_file(pomodoro::files::configuration);
}
