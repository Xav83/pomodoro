#pragma once

#include "shared/Configuration.hpp"
#include <argh.h>

namespace pomodoro::CommandLineParser {
struct Result {
  pomodoro::Configuration conf;
  bool succeed{true};
  std::string errorMessage;
};

Result getConfigurationFromCommandLine(
    const argh::parser &parser,
    const pomodoro::Configuration &defaultConfiguration);
} // namespace pomodoro::CommandLineParser