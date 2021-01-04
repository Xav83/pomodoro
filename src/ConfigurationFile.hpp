#pragma once

#include "Configuration.hpp"
#include <filesystem>

namespace pomodoro {
struct ConfigurationFile {
public:
  explicit ConfigurationFile(std::filesystem::path file);
  ~ConfigurationFile();

  void save(Configuration configurationToSave);
  Configuration load() const;

private:
  std::filesystem::path configuration;
};
} // namespace pomodoro
