#pragma once

#include "Configuration.hpp"
#include <argh.h>

namespace CommandLineParser {
pomodoro::Configuration getConfigurationFromCommandLine(
    argh::parser parser, const pomodoro::Configuration &defaultConfiguration);
}