#include "Fonts.hpp"
#include <fmt/core.h>

#ifdef _WIN32
std::filesystem::path pomodoro::fonts::main =
    "C:/ProgramData/pomodoro/Fonts/Roboto/Roboto-Regular.ttf";
#elif __APPLE__
std::filesystem::path pomodoro::fonts::main = fmt::format(
    "{}/Library/Application Support/Pomodoro/Roboto/Roboto-Regular.ttf",
    std::getenv("HOME"));
#else
// NOLINTNEXTLINE(cert-err58-cpp)
std::filesystem::path pomodoro::fonts::main =
    fmt::format("{}/.pomodoro/Roboto/Roboto-Regular.ttf", std::getenv("HOME"));
#endif
