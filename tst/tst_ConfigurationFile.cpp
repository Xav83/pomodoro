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
  pomodoro::ConfigurationFile conf_file(pomodoro::files::configuration);
  std::filesystem::remove(pomodoro::files::configuration);
}

// NOLINTNEXTLINE
TEST(tst_ConfigurationFile, SaveAndRestoreConfigurationFile) {
  pomodoro::Configuration conf_to_save;
  conf_to_save.setWorkTime(std::chrono::minutes(69));
  {
    pomodoro::ConfigurationFile conf_file(pomodoro::files::configuration);
    conf_file.save(conf_to_save);
  }
  pomodoro::ConfigurationFile conf_file(pomodoro::files::configuration);
  pomodoro::Configuration conf_restored = conf_file.load();

  EXPECT_EQ(conf_to_save, conf_restored);

  std::filesystem::remove(pomodoro::files::configuration);
}
