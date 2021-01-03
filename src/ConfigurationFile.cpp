#include "ConfigurationFile.hpp"
#include "color/Dictionary.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using pomodoro::ConfigurationFile;

ConfigurationFile::ConfigurationFile(const std::filesystem::path &file)
    : configuration(file) {}
ConfigurationFile::~ConfigurationFile() = default;

void ConfigurationFile::save(Configuration configurationToSave) {
  nlohmann::json j;
  j["color_id"] = configurationToSave.getColorId();
  j["work_time"] = configurationToSave.getWorkTime().count();
  j["break_time"] = configurationToSave.getBreakTime().count();
  j["long_break_time"] = configurationToSave.getLongBreakTime().count();

  std::ofstream fileStream(configuration);
  fileStream << std::setw(4) << j << std::endl;
}

pomodoro::Configuration ConfigurationFile::load() const {
  nlohmann::json j;
  {
    std::ifstream fileStream(configuration);
    fileStream >> j;
  }
  return pomodoro::Configuration(j["color_id"],
                                 std::chrono::minutes(j["work_time"]),
                                 std::chrono::minutes(j["break_time"]),
                                 std::chrono::minutes(j["long_break_time"]));
}
