#include "ConfigurationFile.hpp"
#include "color/Dictionary.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using pomodoro::ConfigurationFile;

ConfigurationFile::ConfigurationFile(std::filesystem::path file)
    : configuration(std::move(file)) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(not configuration.empty());
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(not std::filesystem::exists(configuration) or
         std::filesystem::is_regular_file(configuration));
}

ConfigurationFile::~ConfigurationFile() = default;

void ConfigurationFile::save(const Configuration &configurationToSave) {
  nlohmann::json j;
  j["color_id"] = configurationToSave.getColorId();
  j["work_time"] = configurationToSave.getWorkTime().count();
  j["break_time"] = configurationToSave.getBreakTime().count();
  j["long_break_time"] = configurationToSave.getLongBreakTime().count();

  std::ofstream fileStream(configuration);
  try {
    fileStream << std::setw(4) << j << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(std::filesystem::exists(configuration));
}

pomodoro::Configuration ConfigurationFile::load() const {
  nlohmann::json j;
  {
    std::ifstream fileStream(configuration);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    assert(std::filesystem::exists(configuration) and
           std::filesystem::is_regular_file(configuration));
    j = nlohmann::json::parse(fileStream);
  }
  return pomodoro::Configuration(j["color_id"],
                                 std::chrono::minutes(j["work_time"]),
                                 std::chrono::minutes(j["break_time"]),
                                 std::chrono::minutes(j["long_break_time"]));
}
