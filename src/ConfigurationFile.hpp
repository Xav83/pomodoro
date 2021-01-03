#pragma once

#include "Configuration.hpp"
#include <filesystem>

namespace pomodoro {
struct ConfigurationFile {
public:
  explicit ConfigurationFile(const std::filesystem::path &file);
  ~ConfigurationFile();

  void save(Configuration configuration);
  Configuration load() const;

private:
  std::filesystem::path configuration;
};
} // namespace pomodoro
