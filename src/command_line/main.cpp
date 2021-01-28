#include "CommandLineParser.hpp"
#include "shared/ConfigurationFile.hpp"
#include "shared/Pomodoro.hpp"
#include "shared/color/Dictionary.hpp"
#include "shared/utility/FilesDictionary.hpp"
#include "shared/utility/StringsDictionary.hpp"
#include <SFML/Audio.hpp>
#include <fmt/chrono.h>
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

  const auto color_id = configuration.getColorId();

  while (pomodoro.isRunning()) {
    const auto &timer = pomodoro.getCurrentTimer();

    const auto name = [&timer, &color_id]() {
      if (color_id != pomodoro::color::Id::no_color) {
        auto color_set =
            pomodoro::color::dictionary.at(static_cast<size_t>(color_id));
        if (timer.getName() == pomodoro::strings::work_timer) {
          return fmt::format(fg(color_set.work_color), timer.getName().data());
        }
        return fmt::format(fg(color_set.break_color), timer.getName().data());
      }
      return fmt::format(timer.getName().data());
    }();

    fmt::print(pomodoro::strings::current_timer, name,
               timer.getRemainingTime());

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  return EXIT_SUCCESS;
}
