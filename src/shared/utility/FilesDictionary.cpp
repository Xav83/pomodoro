#include "FilesDictionary.hpp"
#include <fmt/core.h>

#ifdef _WIN32
std::filesystem::path pomodoro::files::sounds::start_break =
    "C:/ProgramData/pomodoro/PowerDown1.ogg";
std::filesystem::path pomodoro::files::sounds::start_work =
    "C:/ProgramData/pomodoro/PowerUp1.ogg";
std::filesystem::path pomodoro::files::configuration =
    "C:/ProgramData/pomodoro/save.cfg";
#elif __APPLE__
std::filesystem::path pomodoro::files::sounds::start_break =
    fmt::format("{}/Library/Application Support/Pomodoro/PowerDown1.ogg",
                std::getenv("HOME"));
std::filesystem::path pomodoro::files::sounds::start_work =
    fmt::format("{}/Library/Application Support/Pomodoro/PowerUp1.ogg",
                std::getenv("HOME"));
std::filesystem::path pomodoro::files::configuration = fmt::format(
    "{}/Library/Application Support/Pomodoro/save.cfg", std::getenv("HOME"));
#else
// NOLINTNEXTLINE(cert-err58-cpp)
std::filesystem::path pomodoro::files::sounds::start_break =
    fmt::format("{}/.pomodoro/PowerDown1.ogg", std::getenv("HOME"));
// NOLINTNEXTLINE(cert-err58-cpp)
std::filesystem::path pomodoro::files::sounds::start_work =
    fmt::format("{}/.pomodoro/PowerUp1.ogg", std::getenv("HOME"));
// NOLINTNEXTLINE(cert-err58-cpp)
std::filesystem::path pomodoro::files::configuration =
    fmt::format("{}/.pomodoro/save.cfg", std::getenv("HOME"));
#endif
