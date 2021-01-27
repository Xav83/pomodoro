#include "CommandLineParser.hpp"
#include "shared/ConfigurationFile.hpp"
#include "shared/Pomodoro.hpp"
#include "shared/color/Dictionary.hpp"
#include "shared/utility/FilesDictionary.hpp"
#include "shared/utility/StringsDictionary.hpp"
#include <SFML/Audio.hpp>
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

  auto parsing_result =
      pomodoro::CommandLineParser::getConfigurationFromCommandLine(
          parser, configuration);
  if (not parsing_result.succeed) {
    fmt::print(parsing_result.errorMessage);
    std::terminate();
  }

  configuration = parsing_result.conf;

  if (parser[{"-s", "--set-as-default"}]) {
    configurationFile.save(configuration);
  }

  sf::Music start_break_sound, start_work_sound;

  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(std::filesystem::exists(pomodoro::files::sounds::start_break));
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  assert(std::filesystem::exists(pomodoro::files::sounds::start_work));
  const auto hasOpenBreakSoundSuccessfully = start_break_sound.openFromFile(
      pomodoro::files::sounds::start_break.string());
  assert(hasOpenBreakSoundSuccessfully);
  const auto hasOpenWorkSoundSuccessfully = start_work_sound.openFromFile(
      pomodoro::files::sounds::start_work.string());
  assert(hasOpenWorkSoundSuccessfully);

  Pomodoro pomodoro(
      configuration,
      [&start_break_sound, &start_work_sound]() {
        start_work_sound.stop();
        start_break_sound.play();
        fmt::print("\n");
      },
      [&start_break_sound, &start_work_sound]() {
        start_break_sound.stop();
        start_work_sound.play();
        fmt::print("\n");
      },
      [&start_break_sound, &start_work_sound]() {
        start_break_sound.stop();
        start_work_sound.play();
        fmt::print("\n");
      });
  pomodoro.run();

  while (pomodoro.isRunning()) {
    fmt::print("\r{}", pomodoro.getCurrentState());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  return EXIT_SUCCESS;
}
