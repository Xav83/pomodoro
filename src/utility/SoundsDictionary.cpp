#include "SoundsDictionary.hpp"

#ifdef _WIN32
std::filesystem::path pomodoro::sounds::file::start_break =
    "C:/ProgramData/pomodoro/PowerDown1.ogg";
std::filesystem::path pomodoro::sounds::file::start_work =
    "C:/ProgramData/pomodoro/PowerUp1.ogg";
#elif __APPLE__
std::filesystem::path pomodoro::sounds::file::start_break =
    "~/Library/Application Support/Pomodoro/PowerDown1.ogg";
std::filesystem::path pomodoro::sounds::file::start_work =
    "~/Library/Application Support/Pomodoro/PowerUp1.ogg";
#else
std::filesystem::path pomodoro::sounds::file::start_break =
    "~/.pomodoro/PowerDown1.ogg";
std::filesystem::path pomodoro::sounds::file::start_work =
    "~/pomodoro/PowerUp1.ogg";
#endif
