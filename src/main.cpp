#include "CommandLineParser.hpp"
#include "ConfigurationFile.hpp"
#include "Pomodoro.hpp"
#include "color/Dictionary.hpp"
#include "utility/FilesDictionary.hpp"
#include "utility/StringsDictionary.hpp"
#include <thread>
#include <utility>

int main(int, char *argv[]) {
  argh::parser parser(argv);

  if (parser[{"-h", "--help"}]) {
    fmt::print(pomodoro::strings::help_message);
    return EXIT_SUCCESS;
  }

  pomodoro::ConfigurationFile configurationFile(pomodoro::files::configuration);
  auto configuration = [&configurationFile]() {
    if (std::filesystem::exists(pomodoro::files::configuration)) {
      return configurationFile.load();
    }
    return pomodoro::Configuration();
  }();

  configuration =
      CommandLineParser::getConfigurationFromCommandLine(parser, configuration);

  if (parser[{"-s", "--set-as-default"}]) {
    configurationFile.save(configuration);
  }

  Pomodoro pomodoro(configuration);
  pomodoro.run();

  while (pomodoro.isRunning()) {
    fmt::print("\r{}", pomodoro.getCurrentState());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  return EXIT_SUCCESS;
}
